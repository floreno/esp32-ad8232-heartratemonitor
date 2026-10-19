const fs=require('fs'),path=require('path');
module.exports=function(){
 const config=fs.readFileSync(path.join(__dirname,'../HeartMonitor/config.h'),'utf8');
 return fs.readFileSync(path.join(__dirname,'../HeartMonitor/web_page.h'),'utf8').replace(/\)HTML" HM_STRINGIFY\((\w+)\) R"HTML\(/g,(_,name)=>{
  const match=config.match(new RegExp('^#define '+name+' ([0-9.]+)$','m'));
  if(!match)throw Error('Missing numeric config '+name);
  return match[1];
 });
};
