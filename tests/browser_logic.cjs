const fs=require('fs'),vm=require('vm'),assert=require('assert');
function element(){return {value:'25',children:[],textContent:'',className:'',style:{},open:false,handlers:{},
 addEventListener(type,handler){(this.handlers[type]??=[]).push(handler)},
 dispatch(type,event={}){for(const handler of this.handlers[type]||[])handler(event)},
 showModal(){this.open=true},close(){this.open=false;this.dispatch('close')},focus(){this.focused=true},
 setAttribute(name,value){this[name]=value},removeAttribute(name){delete this[name]},setPointerCapture(){},
 getBoundingClientRect(){return {left:10,top:10,right:610,bottom:610}},
 replaceChildren(){this.children=[]},append(...x){this.children.push(...x)},prepend(x){this.children.unshift(x)},remove(){}};}

const page=require('./read_web_page.cjs')();
assert.match(page, /id="auto-height"[^>]*checked/);
assert.match(page, /id="center"[^>]*checked/);
assert.match(page, /<dialog id="electrode-help" aria-labelledby="electrode-help-title"/);
assert.match(page, /aria-label="Hilfe zur Elektrodenplatzierung" aria-haspopup="dialog"/);
const commonsBody=fs.readFileSync(require('path').join(__dirname,'../assets/human-body-front.svg'),'utf8').match(/<svg[^>]*>([\s\S]*)<\/svg>/)[1];
assert(page.includes(commonsBody),'Original Commons body must be embedded once');
for(const name of ['limbs','torso']){
 const svg=fs.readFileSync(require('path').join(__dirname,'../assets/electrode-'+name+'.svg'),'utf8');
 assert(page.includes(svg.replace(commonsBody,'<use href="#commons-front-body"/>')),'Embedded SVG must match editable asset');
 assert.deepStrictEqual([...svg.matchAll(/<text\b[^>]*>(.*?)<\/text>/gs)].map(match=>match[1]),['RA','LA','RL']);
 assert(svg.includes('class="commons-front"'),'Commons front-view illustration missing');
 assert(svg.includes('#d43f50')&&svg.includes('#e8c434')&&svg.includes('#21895c'),'Requested lead colors missing');
}

const elements=new Map();const get=id=>{if(!elements.has(id))elements.set(id,element());return elements.get(id)};
get('auto-height').checked=true;get('center').checked=true;get('beat-mean').checked=true;get('beat-median').checked=true;
get('voltage-mode').value='output';get('gain').value='100';get('view-mode').value='scroll';
const positions=[],drawnText=[];
const drawing=new Proxy({}, {get:(target,name)=>name==='fillText'?((text,x,y)=>drawnText.push({text,x,y})):name==='moveTo'||name==='lineTo'?((x,y)=>{if(!Number.isFinite(x)||!Number.isFinite(y))throw Error('Invalid canvas coordinate');positions.push([x,y]);}):()=>{}});
get('beat-overlay').clientWidth=900;get('beat-overlay').clientHeight=280;get('beat-overlay').getContext=()=>drawing;
get('plot').clientWidth=900;get('plot').clientHeight=320;get('plot').getContext=()=>drawing;
const context={recording:require('./fixtures/synthetic-75bpm.json').values,positions,drawnText,requestAnimationFrame(){},document:{getElementById:get,createElement:element},window:{addEventListener(){}},URL:{createObjectURL:()=> 'blob:test',revokeObjectURL(){}},Blob,Date,console};
vm.createContext(context);
vm.runInContext(page.match(/<script>([\s\S]*?)<\/script>/)[1].replace(/poll\(\);\s*requestAnimationFrame\(animate\);\s*$/,''),context);
vm.runInContext(`
archiveViewport.clientWidth=800;archiveViewport.clientHeight=400;
const archiveOpener=document.createElement('button');openArchiveImage('blob:viewer-test','Abschnitt Test',archiveOpener);
if(!archiveViewer.open||archiveLarge.src!=='blob:viewer-test')throw Error('Archive viewer did not open');
setArchiveZoom(200);if(archiveView.zoom!==2||archiveLarge.style.width!=='1600px')throw Error('Archive zoom failed');
setArchiveZoom(500);if(archiveView.zoom!==4)throw Error('Archive zoom maximum failed');
document.getElementById('archive-fit').dispatch('click');
if(archiveView.zoom!==1||archiveViewport.scrollLeft!==0)throw Error('Archive fit failed');
archiveViewport.dispatch('pointerdown',{button:0,clientX:200,clientY:150,pointerId:1,preventDefault(){}});
archiveViewport.dispatch('pointermove',{clientX:170,clientY:120});
if(archiveViewport.scrollLeft!==30||archiveViewport.scrollTop!==30)throw Error('Archive panning failed');
archiveViewport.dispatch('pointerup');
archiveViewer.dispatch('click',{target:archiveViewer,clientX:20,clientY:20});if(!archiveViewer.open)throw Error('Inside viewer click closed it');
archiveViewer.dispatch('click',{target:archiveViewer,clientX:0,clientY:0});
if(archiveViewer.open||!archiveOpener.focused||archiveView.url!==null)throw Error('Archive close/focus failed');
openArchiveImage('blob:viewer-test','Test',archiveOpener);closeArchiveImage('blob:other');if(!archiveViewer.open)throw Error('Unrelated archive closed viewer');
closeArchiveImage('blob:viewer-test');if(archiveViewer.open)throw Error('Removed archive did not close viewer');
console.log('PASS: archive large view, zoom bounds, fit, mouse panning, backdrop/focus and URL cleanup');
beatOpen.dispatch('click');
if(!beatDialog.open)throw Error('Beat dialog does not open');
document.getElementById('beat-close').dispatch('click');
if(beatDialog.open||!beatOpen.focused)throw Error('Beat dialog close/focus failed');
beatOpen.dispatch('click');beatDialog.dispatch('click',{target:beatDialog,clientX:20,clientY:20});
if(!beatDialog.open)throw Error('Inside click closed beat dialog');
beatDialog.dispatch('click',{target:beatDialog,clientX:0,clientY:0});
if(beatDialog.open)throw Error('Beat dialog backdrop failed');
let statistics=beatStatistics([Array(71).fill(1),Array(71).fill(3)]);
if(statistics.mean.some(x=>x!==2)||statistics.sd.some(x=>Math.abs(x-Math.sqrt(2))>1e-12))throw Error('Incorrect beat statistics');
if(beatStatistics([Array(71).fill(3)]).sd.some(x=>x!==0)||beatStatistics([]).mean.length)throw Error('Invalid single/empty beat statistics');
console.log('PASS: beat dialog lifecycle, mean and sample standard deviation');
const noisyBeat=Array.from({length:71},(_,i)=>i%2?1:-1);noisyBeat.clipped=true;
const originalBeat=noisyBeat.slice();const smoothedBeat=smoothBeatDisplay(noisyBeat);
if(smoothedBeat.some((value,i)=>!Number.isFinite(value)||Math.abs(value)>1))throw Error('Smoothing invalid or overshoots');
if(smoothedBeat.slice(3,12).some(value=>Math.abs(value)>0.03))throw Error('High-frequency ripple not suppressed');
if(smoothedBeat.slice(21,30).some((value,i)=>value!==noisyBeat[i+21]))throw Error('Aligned peak region changed');
if(noisyBeat.some((value,i)=>value!==originalBeat[i])||!smoothedBeat.clipped)throw Error('Smoothing mutated samples or lost clipping flag');
if(smoothBeatDisplay(Array(71).fill(2)).some(value=>value!==2))throw Error('Smoothing changed constant level');
beatSmoothingEl.checked=true;saveSettings();beatSmoothingEl.checked=false;restoreSettings();
if(!beatSmoothingEl.checked)throw Error('Smoothing setting not restored from cookie');
beatSmoothingEl.checked=false;saveSettings();
drawnText.length=0;drawBeatOverlay();
if(!drawnText.some(t=>t.text==='ms')||!drawnText.some(t=>t.text==='-200')||!drawnText.some(t=>t.text==='400'))throw Error('Sample time labels missing');
console.log('PASS: sample smoothing suppresses ripple, preserves peak/raw data/clipping flag, persists setting and displays time ticks');
beatReferenceEl.checked=true;drawnText.length=0;drawBeatOverlay();
for(const label of ['P','PR','QRS','ST','T'])if(!drawnText.some(t=>t.text===label))throw Error('Reference section missing '+label);
beatReferenceEl.checked=false;drawnText.length=0;drawBeatOverlay();
if(drawnText.some(t=>t.text==='QRS'))throw Error('Reference toggle did not hide template');
saveSettings();beatReferenceEl.checked=true;restoreSettings();
if(beatReferenceEl.checked)throw Error('Reference visibility not restored');
beatReferenceEl.checked=true;saveSettings();
console.log('PASS: schematic P/PR/QRS/ST/T reference, toggle and cookie');


helpOpen.dispatch('click');
if(!helpDialog.open)throw Error('Help does not open');
document.getElementById('electrode-help-close').dispatch('click');
if(helpDialog.open||!helpOpen.focused)throw Error('Help close/focus restoration failed');
helpOpen.dispatch('click');helpDialog.dispatch('click',{target:helpDialog,clientX:20,clientY:20});
if(!helpDialog.open)throw Error('Click inside help closed modal');
helpDialog.dispatch('click',{target:helpDialog,clientX:0,clientY:0});
if(helpDialog.open)throw Error('Backdrop click did not close help');
resetContactGuard();
let cursor=0;
function guardPacket(statuses,header=statuses.at(-1)||0){
 const p={intervalUs:10000,total:cursor+statuses.length,newest:cursor+statuses.length,leadOff:statuses,leadStatus:header,values:statuses.map(s=>s?null:1650)};
 cursor+=statuses.length;stabilizeContact(p);showContactStatus(p);return p;
}
for(let round=0;round<10;round++){
 const p=guardPacket([...Array(20).fill(3),...Array(3).fill(0)],0);
 if(p.contactReady||p.values.some(Number.isFinite)||document.getElementById('contact-status').textContent==='Keine Kontaktfehler gemeldet')throw Error('Brief LOW flash cleared contact fault');
}
let stable=guardPacket(Array(96).fill(0),0);
if(stable.contactReady)throw Error('Contact cleared before one second');
stable=guardPacket([0],0);
if(!stable.contactReady||stable.contactFault||!Number.isFinite(stable.values[0])||document.getElementById('contact-status').textContent!=='Keine Kontaktfehler gemeldet')throw Error('One second stable LOW did not release contact');
const badAgain=guardPacket([1],1);
if(!badAgain.contactReady||Number.isFinite(badAgain.values[0])||badAgain.contactFault)throw Error('Short contact pulse unnecessarily stopped live view');
const recovered=guardPacket([0],0);
if(!Number.isFinite(recovered.values[0])||!recovered.contactReady)throw Error('Short pulse caused extra recovery delay');
let sustained=guardPacket(Array(99).fill(1),1);
if(!sustained.contactReady||sustained.contactFault)throw Error('Fault confirmed before one second');
sustained=guardPacket([1],1);
if(sustained.contactReady||sustained.contactFault!==1)throw Error('One-second fault not confirmed');
const emptyGuard=guardPacket([],0);if(emptyGuard.contactReady)throw Error('Empty packets released contact');
const notYetRecovered=guardPacket(Array(99).fill(0),0);
if(notYetRecovered.contactReady)throw Error('Confirmed fault cleared too early');
const fullyRecovered=guardPacket([0],0);
if(!fullyRecovered.contactReady||fullyRecovered.contactFault)throw Error('Confirmed fault did not recover');
resetContactGuard();
console.log('PASS: one-second contact debounce and release, short impulses keep live view ready, invalid samples stay gaps');
console.log('PASS: help modal opening, closing, backdrop and focus restoration');
function packet(total,count=500){return {total,intervalUs:10000,values:Array.from({length:Math.min(total,count)},(_,i)=>(total-Math.min(total,count)+i)%4096)};}
collectArchive(packet(100));
if(pending.length!==1)throw Error('Initial historical values included');
collectArchive(packet(100));
if(pending.length!==1)throw Error('Duplicate snapshot counted');
collectArchive(packet(599));
if(archiveEntries.length!==1 || pending.length!==0)throw Error('500-value segment boundary incorrect');
collectArchive(packet(620));
if(pending.length!==21)throw Error('Overlapping snapshot incorrect');
collectArchive(packet(1200));
if(archiveEntries.length!==1 || pending.length!==1 || !archiveWarning)throw Error('Missing samples not separated');
for(let t=1220;t<14000;t+=20)collectArchive(packet(t));
if(archiveEntries.length!==20)throw Error('Archive retention limit incorrect');
const settings={interval:10000,units:100,baseline:2048,started:new Date()};
const svg=archiveSvg(Array(1000).fill(2048),settings,false);
if((svg.match(/<polyline/g)||[]).length!==2 || !svg.endsWith('</svg>'))throw Error('SVG rows incorrect');
collectLive(packet(500));
const begin=live.cursor;
advancePlayback(0);advancePlayback(16);
if(!(live.cursor>begin && live.cursor-begin<2))throw Error('Frame does not advance smoothly');
const beforePacket=live.cursor;collectLive(packet(520));
if(live.cursor!==beforePacket)throw Error('Packet arrival moved playback cursor');
collectLive(packet(520));
if(live.values.length!==520)throw Error('Live history duplicated samples');
for(let i=1;i<600;i++)advancePlayback(16+i*16);
if(live.cursor>live.next-1)throw Error('Extrapolation beyond measured samples');
const held=live.cursor;advancePlayback(11000);
if(live.cursor!==held)throw Error('Missing-data playback not held');
paused=true;advancePlayback(11100);
if(live.cursor!==held)throw Error('Pause did not hold cursor');
paused=false;collectLive(packet(1500));
if(live.first!==1000 || live.cursor<1000)throw Error('Gap did not reset live playback');
draw(packet(1500));
function verticalGrid(){
 const lines=[];
 for(let i=0;i+1<positions.length;i+=2){
  const a=positions[i],b=positions[i+1];
  if(a[0]===b[0]&&a[1]===22&&b[1]===288)lines.push(a[0]);
 }
 return lines;
}
viewEl.value='scroll';live.cursor=1200;positions.length=0;draw(packet(1500));const firstGrid=verticalGrid();
live.cursor+=0.5;positions.length=0;draw(packet(1500));const nextGrid=verticalGrid();
const expectedShift=0.5*live.interval/1e6/4.99*824;
if(!firstGrid.length||firstGrid.length!==nextGrid.length||firstGrid.some((x,i)=>Math.abs(x-nextGrid[i]-expectedShift)>1e-8))throw Error('Grid does not move with waveform');
viewEl.value='sweep';positions.length=0;draw(packet(1500));const fixedGrid=verticalGrid().slice(0,-1);
live.cursor+=0.5;positions.length=0;draw(packet(1500));const fixedNext=verticalGrid().slice(0,-1);
if(fixedGrid.some((x,i)=>x!==fixedNext[i]))throw Error('Sweep grid unexpectedly moves');
console.log('PASS: scroll grid follows fractional playback cursor; sweep grid stays fixed');
const axisSaved={mode:voltageEl.value,gain:gainEl.value,zoom:autoHeightEl.checked,center:autoCenterEl.checked,baseline};
voltageEl.value='ecg';gainEl.value='0.1';autoHeightEl.checked=false;autoCenterEl.checked=false;baseline=measurement.referenceMv;
drawnText.length=0;draw(packet(1500));
if(!drawnText.some(t=>t.text==='mV ≈')||!drawnText.some(t=>t.x===56&&Number(t.text.replace(',','.'))===0))throw Error('Estimated ECG axis missing or incorrect');
voltageEl.value='output';gainEl.value='100';baseline=1650;drawnText.length=0;draw(packet(1500));
if(!drawnText.some(t=>t.text==='mV')||!drawnText.some(t=>t.x===56&&t.text==='1650'))throw Error('Output voltage axis missing or incorrect');
voltageEl.value=axisSaved.mode;gainEl.value=axisSaved.gain;autoHeightEl.checked=axisSaved.zoom;autoCenterEl.checked=axisSaved.center;baseline=axisSaved.baseline;
console.log('PASS: live mV axis uses selected voltage mode and reference');

viewEl.value='sweep';live.sweepOrigin=live.cursor;draw(packet(1500));
live.sweepOrigin=live.cursor-600;draw(packet(1500));
for(const signal of [[0,4095],[2048,2048],[2000,2050],[]]){
 const fit=fitHeight(signal,30);
 if(!Number.isFinite(fit.units)||fit.units<=0||!Number.isFinite(fit.center))throw Error('Invalid auto scale');
 for(const v of signal)if(Math.abs((v-fit.center)/fit.units)>12.0001)throw Error('Auto scale clips signal');
}
autoHeightEl.checked=true;draw(packet(1500));
if(!archiveSvg([0,4095],{...settings,autoHeight:true},false).includes('Autozoom'))throw Error('Missing automatic archive scale');
for(const zoom of [false,true])for(const centered of [false,true]){
 const scale=resolveScale([100,300],30,100,2048,zoom,centered);
 if(scale.center!==(centered?200:2048))throw Error('Center checkbox not independent');
 if(!zoom && scale.units!==100)throw Error('Center changed manual zoom');
 if(zoom && [100,300].some(v=>Math.abs(v-scale.center)/scale.units>12.0001))throw Error('Independent zoom clipped');
}
viewEl.value='sweep';gainEl.value='50';autoHeightEl.checked=true;autoCenterEl.checked=true;lengthEl.value='100';
saveSettings();
const storedCookie=document.cookie;
if(!storedCookie.includes('Max-Age=31536000')||!storedCookie.includes('SameSite=Lax'))throw Error('Cookie lifetime or scope missing');
viewEl.value='scroll';gainEl.value='200';autoHeightEl.checked=false;autoCenterEl.checked=false;lengthEl.value='25';
restoreSettings();
if(viewEl.value!=='sweep'||gainEl.value!=='50'||!autoHeightEl.checked||!autoCenterEl.checked||lengthEl.value!=='100'||!gainEl.disabled)throw Error('Cookie round trip failed');
document.cookie='heartmonitor_settings=%invalid';restoreSettings();
document.cookie='heartmonitor_settings='+encodeURIComponent(JSON.stringify({version:1,view:'bad',gain:'999',autozoom:'false',segment:'0'}));restoreSettings();
if(viewEl.value!=='sweep'||gainEl.value!=='50'||!autoHeightEl.checked||lengthEl.value!=='100')throw Error('Invalid settings accepted');
setVoltageMode('ecg');
if(voltageFactor()!==1100 || gainEl.value!=='0.1')throw Error('ECG voltage mode incorrect');
if(!scaleDescription(110,1650,1100,1650).includes('0.100 mV') || !scaleDescription(110,1650,1100,1650).includes('0.000 mV'))throw Error('ECG conversion incorrect');
const ecgSvg=archiveSvg([1650,2200],{...settings,units:110,baseline:1650,ecg:true,factor:1100,reference:1650},false);
if(!ecgSvg.includes('0.100 mV')||!ecgSvg.includes('Verstärkung 1100'))throw Error('ECG archive scale missing');
saveSettings();setVoltageMode('output');restoreSettings();
if(voltageEl.value!=='ecg'||gainEl.value!=='0.1')throw Error('Voltage mode cookie failed');
document.cookie='heartmonitor_settings='+encodeURIComponent(JSON.stringify({version:1,view:'scroll',gain:'200',autozoom:false,center:true,segment:'50'}));
restoreSettings();
if(gainEl.value!=='0.1'||viewEl.value!=='scroll'||!autoCenterEl.checked)throw Error('Legacy ADC cookie migration failed');
function binaryPacket(first,values,session=123,reset=false,newest=first+values.length,leadStatus=0,intervalUs=10000){
 const buffer=new ArrayBuffer(32+values.length*2),view=new DataView(buffer);
 for(const [offset,value] of [[0,0x32534d48],[4,session],[8,first],[12,first+values.length],[16,newest],[20,intervalUs]])view.setUint32(offset,value,true);
 view.setUint16(24,1100,true);view.setUint16(26,1650,true);view.setUint16(28,values.length,true);view.setUint16(30,(reset?1:0)|(leadStatus<<1),true);
 values.forEach((v,i)=>view.setUint16(32+i*2,v,true));return buffer;
}
const sampleBinary=binaryPacket(20,[0,1650,2500,16383]);
const decoded=decodeSamplePacket(sampleBinary);
if(decoded.first!==20||decoded.total!==24||decoded.values.join(',')!=='0,1650,2500,'||decoded.gain!==1100)throw Error('Binary decoding failed');
for(const invalid of [new ArrayBuffer(0),sampleBinary.slice(0,35),binaryPacket(0,Array(129).fill(0))]){
 let rejected=false;try{decodeSamplePacket(invalid);}catch(e){rejected=true;}if(!rejected)throw Error('Invalid packet accepted');
}
const invalidMagic=sampleBinary.slice(0);new DataView(invalidMagic).setUint32(0,0);
try{decodeSamplePacket(invalidMagic);throw Error('Invalid magic accepted');}catch(e){if(e.message==='Invalid magic accepted')throw e;}
transport.session=null;transport.after=null;archiveCursor=null;pending=[];live.values=[];paused=false;
acceptSamplePacket(decodeSamplePacket(binaryPacket(0,Array(20).fill(1650),123,true)));
acceptSamplePacket(decodeSamplePacket(binaryPacket(20,Array(20).fill(1651))));
if(live.values.length!==40||pending.length!==21||transport.after!==40)throw Error('Incremental packet acceptance failed');
acceptSamplePacket(decodeSamplePacket(binaryPacket(0,Array(10).fill(1650),456,true)));
if(live.values.length!==10||pending.length!==1||transport.session!==456||!archiveWarning)throw Error('ESP restart detection failed');
acceptSamplePacket(decodeSamplePacket(binaryPacket(100,Array(10).fill(1650),456,true)));
if(live.first!==100||live.values.length!==10||pending.length!==1)throw Error('Expired cursor not separated');
if(decodeSamplePacket(binaryPacket(110,[],456)).total!==110)throw Error('Empty packet failed');
const leadPacket=decodeSamplePacket(binaryPacket(0,[1650,1651|(1<<14),1652|(2<<14),1653|(3<<14),1654],789,true,5,3));
if(leadPacket.values.join(',')!=='1650,,,,1654'||leadPacket.leadOff.join(',')!=='0,1,2,3,0'||leadPacket.leadStatus!==3)throw Error('Per-sample contact bits incorrectly decoded');
showContactStatus(leadPacket);
if(!document.getElementById('contact-status').textContent.includes('prüfen')||document.getElementById('lead-minus').textContent!=='Rot: nicht verbunden'||document.getElementById('lead-plus').textContent!=='Grün: nicht verbunden')throw Error('Contact warning missing');
showContactStatus({...leadPacket,leadStatus:0});
if(document.getElementById('contact-status').textContent!=='Keine Kontaktfehler gemeldet')throw Error('Contact recovery missing');
for(const bits of [0,1,2,3]){
 showContactStatus({...leadPacket,leadStatus:bits});
 if(document.getElementById('lead-minus').textContent!=='Rot: '+(bits&1?'nicht verbunden':'verbunden')||document.getElementById('lead-plus').textContent!=='Grün: '+(bits&2?'nicht verbunden':'verbunden'))throw Error('Connection labels incorrect');
 if(document.getElementById('lead-yellow').textContent!=='Gelb: '+(bits===3?'nicht verbunden':'verbunden')+' · abgeleitet')throw Error('Incorrect derived yellow status');
}
showContactStatus({...leadPacket,newest:0});
if(document.getElementById('lead-yellow').textContent!=='Gelb: – · abgeleitet')throw Error('Yellow status without measurements');
console.log('PASS: derived yellow indicator for all four red/green combinations and missing measurements');
const gapSvg=archiveSvg([1650,1660,null,1700,1690],{...settings,baseline:1650},false);
if((gapSvg.match(/<polyline/g)||[]).length!==2||gapSvg.includes('NaN')||!gapSvg.includes('Messlücken: 1'))throw Error('Archive bridged contact gap');
const allMissing=archiveSvg([null,null],{...settings,autoHeight:true,autoCenter:true},false);
if(allMissing.includes('<polyline')||allMissing.includes('NaN'))throw Error('All-missing section invalid');
if(resolveScale([null,1650,null],30,100,1650,true,true).center!==1650)throw Error('Null influenced auto scale');
const beforeEmptyCount=archiveEntries.length,beforeEmptySerial=archiveSerial;
for(const emptyValues of [[null,null],[1650],[null,1650,null,1660,null]]){
 pending=emptyValues;segmentSettings={...settings};saveSegment(true);
 if(pending.length||segmentSettings!==null||archiveSerial!==beforeEmptySerial||archiveEntries.length!==beforeEmptyCount)throw Error('Empty graph archived or buffer not cleared');
}
pending=[null,...Array.from({length:51},(_,i)=>1650+i),null];segmentSettings={...settings};saveSegment();
if(archiveSerial!==beforeEmptySerial+1)throw Error('Partial valid curve discarded');
pending=Array(51).fill(1650);segmentSettings={...settings};saveSegment(true);
if(archiveSerial!==beforeEmptySerial+2)throw Error('Valid flat line incorrectly discarded');
const archiveOptions={...settings,baseline:1650,units:20,autoHeight:false,autoCenter:false};
const offscreen=Array(500).fill(4000);
if(hasVisibleArchiveCurve(offscreen,archiveOptions))throw Error('Offscreen curve counted as visible');
if(!hasVisibleArchiveCurve(offscreen,{...archiveOptions,autoHeight:true,autoCenter:true}))throw Error('Visible auto-scaled curve dropped');
const boundary=Array(1000).fill(null);boundary[499]=1650;boundary[500]=1651;
if(hasVisibleArchiveCurve(boundary,archiveOptions))throw Error('Points across row boundary counted as line');
const flashes=Array.from({length:500},(_,i)=>i%30<20?1650+i%20:null);
if(hasVisibleArchiveCurve(flashes,archiveOptions))throw Error('Short interrupted contact flashes archived');
if(hasVisibleArchiveCurve(Array(49).fill(1650),archiveOptions))throw Error('Sub-half-second line accepted');
if(!hasVisibleArchiveCurve(Array(51).fill(1650),archiveOptions))throw Error('Half-second visible trace dropped');
const serialBeforeOffscreen=archiveSerial;
pending=offscreen;segmentSettings={...archiveOptions};saveSegment();
if(archiveSerial!==serialBeforeOffscreen||pending.length||segmentSettings!==null)throw Error('Hidden curve generated archive');
console.log('PASS: offscreen traces, row-boundary single points, short contact flashes and visible duration');
resetHeartAnalysis(true);
const heartSignal=Array.from({length:14000},(_,i)=>{
 const phase=(i%100-50)/100;return 1650+400*Math.exp(-0.5*(phase/0.016)**2);
});
for(let end=3000;end<=14000;end+=100){
 live.values=heartSignal.slice(end-3000,end);live.first=end-3000;live.next=end;live.interval=10000;
 updateHeartAnalysis({total:end,leadStatus:0});
}
if(heart.bpm!==60||heart.beats.length!==100||heart.totalBeats<=100)throw Error('Heart rate or overlay retention failed');
if(heart.beats[0][250]-heart.beats[0][0]<0.25)throw Error('Overlay peak not aligned at zero');
const beatCount=heart.totalBeats;
updateHeartAnalysis({total:14000,leadStatus:0});
if(heart.totalBeats!==beatCount)throw Error('Duplicate packets duplicated heartbeats');
heart.lastArrival=Date.now()-4000;checkHeartFreshness();
if(heart.bpm!==null||document.getElementById('pulse-value').textContent!=='—')throw Error('Stale heart rate still shown');
updateHeartAnalysis({total:14000,leadStatus:0});
if(heart.bpm!==null)throw Error('Repeated empty packet revived stale heart rate');
updateHeartAnalysis({total:14001,leadStatus:1});
if(heart.bpm!==null||!document.getElementById('pulse-note').textContent.includes('kontakt'))throw Error('Contact-loss heart rate still shown');
resetHeartAnalysis(true);
if(heart.beats.length||heart.totalBeats)throw Error('Overlay reset failed');
console.log('PASS: heartbeat ingestion, overlay alignment/100-beat limit, deduplication, stale suppression, contact loss and reset');
live.values=recording.slice();live.first=0;live.next=recording.length;live.interval=10000;
updateHeartAnalysis({total:recording.length,leadStatus:0,contactReady:true});
if(heart.bpm!==75||!heart.beats.length||!heart.beats.some(beat=>beat.clipped))throw Error('Synthetic signal BPM/clipped samples not collected');
const stats=beatStatistics(heart.beats);
if(!stats.mean.length||!stats.median.length)throw Error('Clipped recording missing from statistics');
const clean=Array(71).fill(1),cut=Array(71).fill(100);cut.clipped=true;
if(beatStatistics([clean,cut]).mean.some(value=>value!==50.5))throw Error('All-sample mean incorrect');
beatOpen.dispatch('click');drawBeatOverlay();
if(document.getElementById('overlay-note').textContent.includes('abgeschnitten'))throw Error('Clipping distinction still shown');
beatDialog.close();resetHeartAnalysis(true);
console.log('PASS: synthetic signal detects 75 BPM and collects marked clipped samples with all samples in statistics');
live.values=[];live.first=0;live.next=0;live.cursor=null;
const highRateSignal=Array.from({length:7500},(_,i)=>{const phase=(i%250-125)/250;return 1650+400*Math.exp(-0.5*(phase/0.016)**2);});
for(let end=50;end<=7500;end+=50){
 const data={values:highRateSignal.slice(end-50,end),total:end,intervalUs:4000,leadStatus:0};
 collectLive(data);updateHeartAnalysis(data);
}
if(heart.bpm!==60||!heart.beats.length||heart.beats[0].length!==701||heart.beats[0].intervalSeconds!==0.001)throw Error('250 Hz overlay resolution/BPM failed');
if(heart.beats[0][250]-heart.beats[0][0]<0.25||live.values.length!==7500)throw Error('250 Hz alignment/history duration failed');
const highRateSmooth=smoothBeatDisplay(heart.beats[0]);
if(highRateSmooth[250]!==heart.beats[0][250])throw Error('250 Hz smoothing moved peak');
const highStats=beatStatistics(heart.beats);if(highStats.mean.length!==701||highStats.mean.intervalSeconds!==0.001||highStats.mean.preSeconds!==0.25)throw Error('250 Hz statistics truncated or misaligned');
measureEl.checked=true;drawBeatOverlay();
if(!measureState.available||measureFields[0].disabled)throw Error('Manual measurement not enabled for mean');
const initialIntervals=measureIntervals(measureState.marks);
if(initialIntervals.PR!==180||initialIntervals.QRS!==80||initialIntervals.QT!==400)throw Error('Interval math wrong');
setMeasureMark(0,-216);drawBeatOverlay();
if(measureIntervals(measureState.marks).PR!==176||!document.getElementById('measure-results').textContent.includes('176 ms'))throw Error('Interval display did not update');
setMeasureMark(1,200);if(measureState.marks[1]!==measureState.marks[2]-1)throw Error('Markers crossed');
if(setMeasureMark(2,NaN))throw Error('Invalid marker accepted');
document.getElementById('measure-reset').dispatch('click');
const g=measureState.geometry;
const startX=g.left+(g.right-g.left)*(measureState.marks[0]+250)/700;
const pointerClient=x=>10+x/measureCanvas.clientWidth*600;
measureCanvas.dispatch('pointerdown',{button:0,clientX:pointerClient(startX),pointerId:2,preventDefault(){}});
if(measureState.drag!==0)throw Error('Measurement drag target not selected');
measureCanvas.dispatch('pointermove',{clientX:pointerClient(startX+(g.right-g.left)*8/700),preventDefault(){}});
if(measureState.marks[0]!==-212)throw Error('Measurement drag did not map ms');
beatReferenceEl.checked=true;positions.length=0;drawBeatOverlay();const withReference=positions.length;
beatReferenceEl.checked=false;positions.length=0;drawBeatOverlay();
if(withReference-positions.length!==351)throw Error('Reference must remain visible during marker measurement');
beatReferenceEl.checked=true;

measureCanvas.dispatch('pointerup');if(measureState.drag!==null)throw Error('Measurement drag not released');
updateMeasurement([]);if(measureState.available||!measureFields[0].disabled||!document.getElementById('measure-results').textContent.includes('Keine eingeblendete'))throw Error('Measurement allowed without mean');
measureEl.checked=false;drawBeatOverlay();
console.log('PASS: manual mean markers, ms durations, ordering, pointer drag and no-mean guard');
resetHeartAnalysis(true);live.values=[];live.first=0;live.next=0;live.cursor=null;
for(let end=100;end<=15000;end+=100){
 const data={values:Array.from({length:100},(_,j)=>{const phase=((end-100+j)%500-250)/500;return 1650+400*Math.exp(-0.5*(phase/0.016)**2);}),total:end,intervalUs:2000,leadStatus:0};
 collectLive(data);updateHeartAnalysis(data);
}
if(heart.bpm!==60||!heart.beats.length||heart.beats[0].length!==701||live.values.length!==15000)throw Error('500 Hz stream/overlay failed');
let contact500={values:Array(499).fill(1650),leadOff:Array(499).fill(0),leadStatus:0,intervalUs:2000};resetContactGuard();stabilizeContact(contact500);
if(contact500.contactReady)throw Error('500 Hz guard released early');
contact500={values:[1650],leadOff:[0],leadStatus:0,intervalUs:2000};stabilizeContact(contact500);if(!contact500.contactReady)throw Error('500 Hz guard did not release');
const exampleA=Array(351).fill(1),exampleB=Array(351).fill(3),exampleC=Array(351).fill(100);exampleC.clipped=true;
for(const example of [exampleA,exampleB,exampleC]){example.intervalSeconds=0.002;example.preSeconds=0.25;}
const allStats=beatStatistics([exampleA,exampleB,exampleC]);
if(allStats.mean[0]!==104/3||allStats.median[0]!==3||allStats.median.intervalSeconds!==0.002)throw Error('Mean/median over all samples incorrect');
const evenStats=beatStatistics([exampleA,exampleB]);if(evenStats.median[0]!==2)throw Error('Even-count median incorrect');
if(beatStatistics([]).median.length)throw Error('Empty median incorrect');
const cached=beatDisplayData();if(beatDisplayData()!==cached)throw Error('Statistics cache not reused');
beatMeanEl.checked=false;beatMedianEl.checked=true;saveSettings();beatMeanEl.checked=true;beatMedianEl.checked=false;restoreSettings();
if(beatMeanEl.checked||!beatMedianEl.checked)throw Error('Mean/median cookie failed');
beatMeanEl.checked=true;beatMedianEl.checked=true;saveSettings();
resetHeartAnalysis(true);
console.log('PASS: 500 Hz ingestion, aligned 351-point samples, contact guard, inclusive mean/odd-even median, cache and independent cookies');
live.values=[];live.timingMissing=[];live.cursor=null;live.first=0;live.next=0;
for(let end=100;end<=15000;end+=100){
 const vals=Array.from({length:100},(_,j)=>{const i=end-100+j,phase=(i%500-250)/500;return i%500===300?null:1650+400*Math.exp(-0.5*(phase/0.016)**2);});
 const data={values:vals,timingMissing:vals.map(v=>v===null),total:end,intervalUs:2000,leadStatus:0};
 collectLive(data);updateHeartAnalysis(data);
}
if(heart.bpm!==60||heart.beats.length<25||!heart.beats.some(beat=>beat.some(value=>value===null)))throw Error('Small periodic timing gaps still prevent samples');
if(!live.values.some(value=>value===null))throw Error('Raw timing gaps were filled');
const sparseA=Array(351).fill(1),sparseB=Array(351).fill(3);sparseA[100]=null;
const sparseStats=beatStatistics([sparseA,sparseB]);
if(sparseStats.mean[100]!==3||sparseStats.median[100]!==3||sparseStats.mean[101]!==2)throw Error('Missing points biased statistics');
beatOpen.dispatch('click');drawBeatOverlay();beatDialog.close();resetHeartAnalysis(true);
console.log('PASS: 500 Hz samples survive isolated timing gaps, preserve empty raw points and compute statistics from available measurements');
live.values=[];live.timingMissing=[];live.cursor=null;live.first=0;live.next=0;
for(let end=100;end<=10000;end+=100){
 const vals=Array.from({length:100},(_,j)=>{const i=end-100+j,phase=(i%500-250)/500;return i%500>=300&&i%500<320?null:1650+400*Math.exp(-0.5*(phase/0.016)**2);});
 const data={values:vals,timingMissing:vals.map(v=>v===null),total:end,intervalUs:2000,leadStatus:0};collectLive(data);updateHeartAnalysis(data);
}
if(heart.bpm!==60||heart.beats.length<15||!heart.beats.some(beat=>beat.missingCount>=20))throw Error('40 ms holes prevent BPM or sample collection');
resetHeartAnalysis(true);
console.log('PASS: 500 Hz streams with repeated 40 ms timing gaps retain BPM and samples without filling displayed holes');
live.values=[];live.timingMissing=[];live.cursor=null;live.first=0;live.next=0;
for(let end=100;end<=10000;end+=100){
 const vals=Array.from({length:100},(_,j)=>{const i=end-100+j,phase=(i%1000-500)/1000;return i%1000>=600&&i%1000<640?null:1650+400*Math.exp(-0.5*(phase/0.016)**2);});
 const data={values:vals,timingMissing:vals.map(v=>v===null),total:end,intervalUs:1000,leadStatus:0};collectLive(data);updateHeartAnalysis(data);
}
if(heart.bpm!==60||heart.beats.length<7||heart.beats[0].length!==701||!heart.beats.some(beat=>beat.missingCount>=20))throw Error('1000 Hz with 40 ms gaps failed');
if(heart.beats[0][250]-heart.beats[0][0]<0.25||timingGapLimits(0.001).maxSamples!==40)throw Error('1000 Hz peak/timing tolerance misaligned');
beatOpen.dispatch('click');drawBeatOverlay();beatDialog.close();
resetContactGuard();const c1000={values:Array(999).fill(1650),leadOff:Array(999).fill(0),leadStatus:0,intervalUs:1000};stabilizeContact(c1000);if(c1000.contactReady)throw Error('1000 Hz guard released early');
const c1000last={values:[1650],leadOff:[0],leadStatus:0,intervalUs:1000};stabilizeContact(c1000last);if(!c1000last.contactReady)throw Error('1000 Hz guard failed');
resetHeartAnalysis(true);
resetContactGuard();
for(let i=0;i<1100;i++){
 const hole=i%50===25;
 const packet={values:[hole?null:1650],leadOff:[0],timingMissing:[hole],leadStatus:0,intervalUs:1000};stabilizeContact(packet);
}
if(!contactGuard.ready||contactGuard.lastFault)throw Error('Startup never releases with small timing gaps');
resetContactGuard();const lowBefore={values:Array(100).fill(1650),leadOff:Array(100).fill(0),timingMissing:Array(100).fill(false),intervalUs:2000,leadStatus:0};stabilizeContact(lowBefore);
const longMissing={values:Array(21).fill(null),leadOff:Array(21).fill(0),timingMissing:Array(21).fill(true),intervalUs:2000,leadStatus:0};stabilizeContact(longMissing);
if(contactGuard.lowSamples!==0||contactGuard.ready)throw Error('Long timing gap falsely qualified contact');
console.log('PASS: startup contact guard releases with short timing holes but not long gaps');
const bridgeRaw=[1650,null,null,1700],bridgeMask=[false,true,true,false];
if(JSON.stringify(timingBridgeSegments(bridgeRaw,bridgeMask,0.001))!=='[[0,3]]')throw Error('Short timing bridge missing');
if(timingBridgeSegments(bridgeRaw,[false,false,false,false],0.001).length)throw Error('Contact gap bridged');
if(timingBridgeSegments([null,1650],[true,false],0.001).length)throw Error('Unbounded gap bridged');
if(timingBridgeSegments([1650,...Array(41).fill(null),1700],[false,...Array(41).fill(true),false],0.001).length)throw Error('Long timing gap bridged');
const bridgeSvg=archiveSvg(bridgeRaw,{...settings,interval:1000,timingMissing:bridgeMask},false);
if(!bridgeSvg.includes('data-timing-gap="true"')||!bridgeSvg.includes('stroke-opacity="0.9"')||bridgeRaw[1]!==null)throw Error('SVG bridge style or raw preservation failed');
if(archiveSvg(bridgeRaw,{...settings,interval:1000},false).includes('data-timing-gap="true"'))throw Error('Unknown archive gap bridged');
console.log('PASS: 90-percent black timing connectors, contact/long/end gaps preserved, SVG styling and unchanged raw values');

transport.session=null;transport.after=null;archiveCursor=null;pending=[];live.values=[];live.timingMissing=[];live.cursor=null;paused=false;resetHeartAnalysis(true);
for(let first=0;first<10000;first+=100){
 const words=Array.from({length:100},(_,j)=>{const i=first+j,phase=(i%1000-500)/1000;return i%500>=300&&i%500<310?0x3fff:Math.round(1650+400*Math.exp(-0.5*(phase/0.016)**2));});
 acceptSamplePacket(decodeSamplePacket(binaryPacket(first,words,987,first===0,first+100,0,1000)));
}
if(!contactGuard.ready||!live.values.some(Number.isFinite)||heart.bpm!==60||heart.beats.length<7||heart.beats[0].length!==701)throw Error('1000 Hz complete startup/transport/contact/BPM/sample pipeline failed');
resetHeartAnalysis(true);
console.log('PASS: 1000 Hz complete binary transport/startup/contact/live/BPM/sample pipeline with regular timing gaps');







beatOpen.dispatch('click');drawBeatOverlay();beatDialog.close();
resetContactGuard();let contact250={values:Array(249).fill(1650),leadOff:Array(249).fill(0),leadStatus:0,intervalUs:4000};stabilizeContact(contact250);
if(contact250.contactReady)throw Error('250 Hz contact guard released early');
contact250={values:[1650],leadOff:[0],leadStatus:0,intervalUs:4000};stabilizeContact(contact250);
if(!contact250.contactReady)throw Error('250 Hz one-second contact guard failed');
let fault250={values:Array(249).fill(null),leadOff:Array(249).fill(3),leadStatus:3,intervalUs:4000};stabilizeContact(fault250);
if(!fault250.contactReady||fault250.contactFault)throw Error('250 Hz debounce fired early');
const emptyFault={values:[],leadOff:[],leadStatus:3,intervalUs:4000};stabilizeContact(emptyFault);
if(!emptyFault.contactReady||emptyFault.contactFault)throw Error('Header advanced debounce');
fault250={values:[null],leadOff:[3],leadStatus:3,intervalUs:4000};stabilizeContact(fault250);
if(fault250.contactReady||fault250.contactFault!==3)throw Error('250 Hz fault not confirmed after one second');

resetHeartAnalysis(true);
console.log('PASS: 250 Hz live ingestion, 30-second history, 351-point aligned samples/statistics, smoothing and contact guard');
viewEl.value='sweep';live.values=[];live.cursor=null;
collectLive({values:Array(128).fill(1650),total:128,intervalUs:4000});
live.cursor=100;live.sweepOrigin=0;const heldSweepOrigin=live.sweepOrigin;
collectLive({values:Array(700).fill(1650),total:828,intervalUs:4000});
if(live.cursor!==100||live.sweepOrigin!==heldSweepOrigin)throw Error('Backlog restarted sweep early');
const missingPacket=decodeSamplePacket(binaryPacket(0,[1650,0x3fff,1651],123,true));
if(missingPacket.values[1]!==null||missingPacket.leadOff[1]!==0||missingPacket.leadStatus!==0)throw Error('Timing gap decoded as voltage or contact fault');
resetContactGuard();contactGuard.ready=true;contactGuard.lowSamples=250;
const missingStatus={values:[null],leadOff:[0],leadStatus:0,intervalUs:4000};stabilizeContact(missingStatus);
if(!missingStatus.contactReady||missingStatus.contactFault||missingStatus.values[0]!==null)throw Error('Timing gap changed electrode status');
resetPlayback();live.cursor=1240;live.sweepOrigin=0;positions.length=0;draw({});
const headBefore=positions.filter(([x,y])=>y===22).at(-1)[0];
live.cursor=1248;positions.length=0;draw({});const headAfter=positions.filter(([x,y])=>y===22).at(-1)[0];
if(!(headBefore>880&&headAfter<70))throw Error('Sweep did not wrap only at full width');
console.log('PASS: 250 Hz backlog preserves sweep origin; timed gap stays invalid without contact fault; full-width sweep wrap');



console.log('PASS: empty/isolated-point sections discarded, valid partial and flat curves retained');
console.log('PASS: individual LO status combinations, contact recovery, per-sample gaps, archive gaps and auto-scale');
console.log('PASS: binary decoding, malformed packets, incremental ingestion, boot-session changes and expired cursors');
console.log('PASS: ECG conversion, archive units, voltage mode persistence, legacy-cookie migration');
console.log('PASS: cookie round trip, disabled-state restoration, malformed cookie and invalid values');
console.log('PASS: independent centering and zoom, all four checkbox combinations');
console.log('PASS: automatic height, constant signals, full ADC range, empty input, archive scale');
console.log('PASS: scroll and sweep rendering with finite coordinates, including sweep wrap');
console.log('PASS: smooth frame advance, no packet jumps, live deduplication, no extrapolation, pause, gap recovery');
console.log('PASS: first sample, deduplication, segment boundaries, interruption handling, 20-image limit, multi-row SVG');
`,context);

if(process.argv[2]){
 const bytes=fs.readFileSync(process.argv[2]);
 context.nativePacket=bytes.buffer.slice(bytes.byteOffset,bytes.byteOffset+bytes.byteLength);
 vm.runInContext(`const native=decodeSamplePacket(nativePacket);
 if(native.session!==0x12345678||native.first!==1490||native.total!==1500||native.values[0]!==1490||native.values[9]!==1499)throw Error('Native encoder/browser decoder mismatch');
 console.log('PASS: native C++ encoder to browser JavaScript decoder');`,context);
}

(async()=>{
  vm.runInContext('transport.session=456;transport.after=110;',context);
  const scheduled=[];
  let requested='';
  context.AbortController=AbortController;
  context.setTimeout=(fn,ms)=>{scheduled.push(ms);return scheduled.length;};
  context.clearTimeout=()=>{};
  context.fetch=async(url)=>{
    requested=url;
    return {ok:true,arrayBuffer:async()=>vm.runInContext('binaryPacket(110,Array(20).fill(1650),456,false,200)',context)};
  };
  await vm.runInContext('poll()',context);
  assert.strictEqual(requested,'/api/samples.bin?session=456&after=110');
  assert.strictEqual(scheduled.at(-1),0,'Backlog should trigger immediate next packet');
  context.fetch=async()=>{throw Error('network interrupted');};
  await vm.runInContext('poll()',context);
  assert.strictEqual(vm.runInContext('transport.after',context),130,'Failed requests must retain cursor');
  assert.strictEqual(scheduled.at(-1),100);
  console.log('PASS: incremental HTTP query, immediate backlog retry, cursor retention after failed request');
})().catch(error=>{console.error(error);process.exitCode=1;});
