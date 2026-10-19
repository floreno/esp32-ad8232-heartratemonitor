const fs=require('fs'),vm=require('vm'),assert=require('assert'),path=require('path');
const source=require('./read_web_page.cjs')();
const context={console};vm.createContext(context);
vm.runInContext(source.slice(source.indexOf('function median('),source.indexOf('const heart=')),context);
vm.runInContext(`
function synthetic(peaks,seconds=30,polarity=1,rate=100){
 return Array.from({length:Math.round(seconds*rate)},(_,i)=>{
  const t=i/rate;
  let value=1650+25*Math.sin(t*1.4)+3*Math.sin(t*83);
  const gaussian=(x,width)=>Math.exp(-0.5*(x/width)**2);
  for(const peak of peaks){
   const x=t-peak;if(Math.abs(x)>0.6)continue;
   value+=polarity*500*(gaussian(x,0.012)-0.18*gaussian(x+0.025,0.009)-0.25*gaussian(x-0.025,0.012)+0.12*gaussian(x+0.18,0.04)+0.3*gaussian(x-0.24,0.06));
  }
  return value;
 });
}
for(const bpm of [40,60,75,120,180]){
 const peaks=[];for(let t=1;t<29.5;t+=60/bpm)peaks.push(t);
 for(const polarity of [1,-1]){
  const result=detectHeartbeats(synthetic(peaks,30,polarity),0,10000);
  if(result.bpm===null || Math.abs(result.bpm-bpm)>3)throw Error('Synthetic '+bpm+' bpm polarity '+polarity+': '+JSON.stringify(result));
  if(result.arrow!=='→')throw Error('Stable rate trend failed');
  console.log('PASS: '+bpm+' bpm, polarity '+polarity+' -> '+result.bpm);
 }
}
for(const polarity of [1,-1]){
 const short=synthetic([0.4,0.9,1.4],2,polarity);
 const result=detectHeartbeats(short,0,10000);
 if(result.bpm!==120 || !result.reason.includes('2 Schlagabständen'))throw Error('Two-second startup failed: '+JSON.stringify(result));
 if(detectHeartbeats(short.slice(0,199),0,10000).bpm!==null)throw Error('Startup before two seconds');
 const broken=short.slice();broken[100]=null;
 if(detectHeartbeats(broken,0,10000).bpm!==null)throw Error('Short startup bridged contact gap');
}
console.log('PASS: two-second startup with three peaks, both polarities; shorter and interrupted windows rejected');
for(const rate of [250,500,1000])for(const bpm of [40,60,75,120,180]){
 const times=[];for(let t=1;t<29.5;t+=60/bpm)times.push(t);
 for(const polarity of [1,-1]){
  const result=detectHeartbeats(synthetic(times,30,polarity,rate),0,1000000/rate);
  if(result.bpm===null||Math.abs(result.bpm-bpm)>2)throw Error(rate+' Hz detection failed '+bpm+' '+JSON.stringify(result));
 }
}
console.log('PASS: 250/500/1000 Hz heartbeat detection at 40–180 BPM, both polarities');
const gapPeaks=[];for(let t=0.5;t<29.5;t+=1)gapPeaks.push(t);
const gapValues=synthetic(gapPeaks,30,1,500),timingMask=gapValues.map((_,i)=>i%500===300);
timingMask.forEach((missing,i)=>{if(missing)gapValues[i]=null;});
if(detectHeartbeats(gapValues,0,2000,timingMask).bpm!==60)throw Error('Isolated timing holes broke heartbeat detection');
if(detectHeartbeats(gapValues,0,2000).bpm!==null)throw Error('Contact gaps were incorrectly bridged');
if(!gapValues.some(value=>value===null))throw Error('Detector changed input data');
const longHoles=gapValues.slice(),longMask=timingMask.slice();longHoles.fill(null,14900,14930);longMask.fill(true,14900,14930);
if(detectHeartbeats(longHoles,0,2000,longMask).bpm!==null)throw Error('Long timing gap was bridged');
const dense=Array(1000).fill(1650),denseMask=dense.map((_,i)=>i%5===0);
denseMask.forEach((missing,i)=>{if(missing)dense[i]=null;});
if(!prepareTimingAnalysis(dense,denseMask,0.002).some(value=>value===null))throw Error('Dense missing data was filled');
console.log('PASS: isolated timing holes tolerated, contact/long/dense gaps remain invalid, raw values unchanged');
const bursts=synthetic(gapPeaks,30,1,500),burstMask=bursts.map((_,i)=>i%500>=300&&i%500<320);
burstMask.forEach((missing,i)=>{if(missing)bursts[i]=null;});
if(timingGapLimits(0.002).maxSamples!==20||timingGapLimits(0.01).maxSamples!==4)throw Error('Timing tolerance not scaled by interval');
if(detectHeartbeats(bursts,0,2000,burstMask).bpm!==60)throw Error('40 ms timing bursts still block BPM');
if(detectHeartbeats(bursts,0,2000).bpm!==null)throw Error('40 ms contact bursts incorrectly bridged');
console.log('PASS: configurable 40 ms timing tolerance (20 samples at 500 Hz), burst BPM and contact exclusion');

const peaks=[];for(let t=1;t<25;t+=1)peaks.push(t);
const flat=Array(3000).fill(1650);
if(detectHeartbeats(flat,0,10000).bpm!==null)throw Error('Flat line has pulse');
const mains=flat.map((v,i)=>v+100*Math.sin(i*0.01*2*Math.PI*40));
if(detectHeartbeats(mains,0,10000).bpm!==null)throw Error('High frequency interference has pulse');
for(const bad of [null,0,2500,3013]){
 const values=synthetic(peaks);values.fill(bad,values.length-10);
 if(detectHeartbeats(values,0,10000).bpm!==null)throw Error('Invalid latest signal has pulse');
}
console.log('PASS: flat signal, high-frequency interference, contact loss and clipped values rejected');
const alternating=Array.from({length:500},(_,i)=>i%2?3000:0);
if(detectHeartbeats(alternating,0,10000).bpm!==null)throw Error('Clipped alternating interference accepted');
for(const polarity of [1,-1]){
 const clipped=Array.from({length:3000},(_,i)=>{const x=(i%100-50)/100;const spike=800*Math.exp(-0.5*(x/0.016)**2);return polarity>0?Math.min(2200+spike,2500):Math.max(300-spike,0);});
 const result=detectHeartbeats(clipped,0,10000);
 if(result.bpm!==60)throw Error('Brief clipped beats rejected '+JSON.stringify(result));
}
console.log('PASS: brief clipped peaks accepted in both polarities; alternating saturation rejected');

// Nur die letzten sechs Intervalle ändern sich, damit ein aktueller Trend vergleichbar ist.
for(const direction of ['up','down']){
 const sequence=[1];
 for(let i=0;i<20;i++)sequence.push(sequence.at(-1)+(i<17?(direction==='up'?1:0.8):(direction==='up'?0.8:1)));
 const duration=sequence.at(-1)+0.6;
 const result=detectHeartbeats(synthetic(sequence,duration),0,10000);
 const expected=direction==='up'?'↑':'↓';
 if(result.arrow!==expected)throw Error('Trend '+direction+' failed: '+JSON.stringify(result));
 console.log('PASS: trend '+expected);
}
`,context);
