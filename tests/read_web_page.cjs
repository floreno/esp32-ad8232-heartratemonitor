const fs=require('fs'),path=require('path');
module.exports=function(){
 const config=fs.readFileSync(path.join(__dirname,'../HeartMonitor/config.h'),'utf8');
 const translations=fs.readFileSync(path.join(__dirname,'../HeartMonitor/translations.h'),'utf8').match(/R"I18N\(([\s\S]*)\)I18N"/)[1];
 return fs.readFileSync(path.join(__dirname,'../HeartMonitor/web_page.h'),'utf8')
 .replace(/\)HTML"\s*#include "translations.h"\s*R"HTML\(/,()=>translations)
 .replace(/\)HTML" HM_STRINGIFY\((\w+)\) R"HTML\(/g,(_,name)=>{
  const match=config.match(new RegExp('^#define '+name+' ([0-9.]+)$','m'));
  if(!match)throw Error('Missing numeric config '+name);
  return match[1];
 });
};
