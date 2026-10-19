#pragma once
#include <pgmspace.h>
#include "config.h"
#define HM_STRINGIFY_INNER(value) #value
#define HM_STRINGIFY(value) HM_STRINGIFY_INNER(value)

const char WEB_PAGE[] PROGMEM = R"HTML(<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title data-i18n="s0">HeartMonitor · Local</title>
<style>
:root{color-scheme:dark;font-family:system-ui,sans-serif;background:#101923;color:#ecf3fa}body{margin:0;padding:24px;box-sizing:border-box}header{display:flex;align-items:center;justify-content:space-between;gap:20px}h1{font-size:clamp(24px,5vw,36px);margin-bottom:6px}.muted{color:#9eb1c2}main{margin-top:28px;background:#182634;border:1px solid #304355;border-radius:18px;padding:20px}.readout{display:flex;justify-content:space-between;align-items:center;gap:20px}strong{font-size:40px;font-variant-numeric:tabular-nums}canvas{display:block;width:100%;height:320px;margin-top:16px}.archive-card{border:1px solid #304355;border-radius:12px;padding:14px;margin-top:16px}.archive-card img{display:block;width:100%;background:#fffafa;margin:12px 0}.download{display:inline-block;color:#52e3b1;margin-right:16px}#archive-note{line-height:1.5}select{padding:9px;border-radius:8px;background:#263e50;color:#ecf3fa;border:1px solid #587184}label{font-size:14px}.controls{display:flex;flex-wrap:wrap;align-items:center;gap:12px;margin-top:16px}button{border:1px solid #587184;border-radius:8px;padding:10px 18px;background:#263e50;color:inherit;cursor:pointer}#status{font-size:14px}footer{margin-top:20px;font-size:14px;line-height:1.6}@media(max-width:500px){body{padding:14px}main{padding:12px}canvas{height:260px}}

.contact-row{display:flex;align-items:center;gap:12px}.contact-row p{flex:1}.help-icon{width:38px;height:38px;min-width:38px;padding:0;border-radius:50%;font-size:22px;font-weight:700}.help-icon:focus-visible,dialog button:focus-visible{outline:3px solid #52e3b1;outline-offset:3px}
dialog{width:min(960px,calc(100vw - 28px));max-height:85vh;max-height:calc(100dvh - 28px);box-sizing:border-box;overflow:auto;border:1px solid #526b7f;border-radius:18px;background:#162532;color:#ecf3fa;padding:22px}dialog::backdrop{background:rgba(5,12,20,.78)}.help-heading{display:flex;align-items:flex-start;justify-content:space-between;gap:16px}.help-heading h2{margin:0;font-size:clamp(22px,4vw,30px)}.help-heading button{white-space:nowrap}.placement-grid{display:grid;grid-template-columns:repeat(2,minmax(0,1fr));gap:16px}.placement-card{margin:0;padding:14px;background:white;color:#253544;border-radius:14px}.placement-card h3{margin:0 0 8px;font-size:18px}.placement-card svg{display:block;width:100%;height:auto}.help-tips{line-height:1.6}.help-tips a{color:#8dcfff}.help-colors{padding:12px;background:#23394a;border-radius:10px;line-height:1.6}@media(max-width:650px){dialog{padding:14px}.placement-grid{grid-template-columns:1fr}.help-heading{flex-wrap:wrap}.help-heading button{margin-left:auto}}
.sr-only{position:absolute!important;width:1px;height:1px;padding:0;margin:-1px;overflow:hidden;clip:rect(0,0,0,0);white-space:nowrap;border:0}.help-heading{justify-content:flex-end}.help-close{font-size:28px;line-height:1;width:44px;height:44px;padding:0;margin-bottom:12px}

/* Compact monitor layout: live signal first, secondary controls on demand. */
*{box-sizing:border-box}body{padding:20px clamp(12px,2vw,32px);background:#0d151e}header{gap:12px}h1{font-size:25px;margin:0;letter-spacing:-.7px}header .muted{font-size:12px;margin-top:4px}#status{border:1px solid #304355;border-radius:20px;padding:7px 12px;font-size:12px}main{margin-top:18px;padding:18px;border-radius:16px;background:#15222e}.readout{align-items:flex-start}.readout strong{font-size:48px;line-height:1.2}.readout .muted{font-size:12px}#pulse-note{margin-top:4px;max-width:650px}.monitor-top{display:grid;grid-template-columns:minmax(0,1fr) minmax(340px,420px);align-items:start;gap:18px}.contact-panel{padding:10px 12px;border:1px solid #304355;border-radius:12px;background:#111d28}.contact-row{gap:8px}.contact-row p{margin:0;font-size:13px;line-height:1.5}.help-icon{width:28px;height:28px;min-width:28px;font-size:17px}.lead-status{display:grid;grid-template-columns:repeat(3,minmax(0,1fr));gap:8px;margin-top:8px;font-size:12px}.lead-status span{display:block;min-width:0;min-height:56px;padding:6px 8px;border-radius:6px;background:#20313f;overflow-wrap:anywhere}.contact-panel{min-width:0}.contact-row p{min-height:3em}#lead-minus{border-left:3px solid #ed6572}#lead-plus{border-left:3px solid #55c894}#lead-yellow{border-left:3px solid #e8c434}#plot{height:clamp(280px,46vh,520px);margin-top:18px;border-radius:10px}#caption{font-size:11px;line-height:1.6;margin-top:8px}.live-toolbar{display:flex;flex-wrap:wrap;justify-content:space-between;align-items:center;gap:12px;margin-top:14px}.live-toolbar .controls{margin:0}.controls{gap:14px}label{font-size:13px}select,button{font:inherit;font-size:13px;padding:8px 12px}select:disabled{opacity:.45}input[type=checkbox]{accent-color:#52e3b1;vertical-align:middle}button:hover{background:#345166}button:focus-visible,select:focus-visible,summary:focus-visible{outline:2px solid #52e3b1;outline-offset:3px}details.panel{margin-top:16px;border:1px solid #304355;border-radius:12px;background:#15222e}summary{cursor:pointer;padding:15px 18px;font-weight:600;font-size:14px}summary .muted{font-size:12px;font-weight:400;margin-left:8px}.panel-body{padding:0 18px 18px}.panel-body>p{font-size:12px;line-height:1.6}#display-settings{margin-top:14px;border-top:1px solid #304355}#display-settings summary{padding:12px 0;font-size:13px;color:#b9cbd9}#display-settings .controls{margin:0 0 6px}#beat-overlay{height:250px;border-radius:10px}#archive-list{display:grid;grid-template-columns:repeat(auto-fit,minmax(min(100%,380px),1fr));gap:12px}.archive-card{margin:0;padding:12px;min-width:0}.archive-card h3{font-size:14px}.archive-card p,.archive-card a{font-size:12px}.archive-card img{max-height:240px;object-fit:contain;border-radius:6px}.archive-toolbar{justify-content:space-between}.archive-info{font-size:12px;line-height:1.6}.archive-info summary{padding:8px 0;font-size:12px;color:#9eb1c2}footer{font-size:12px;margin-top:18px}footer details{margin-top:8px}footer summary{padding:8px 0;font-size:12px}footer p{max-width:1000px;margin-top:0}h2{font-size:16px}@media(max-width:760px){.monitor-top{grid-template-columns:1fr}.contact-panel{padding:10px}.readout strong{font-size:42px}main{padding:12px}.live-toolbar{align-items:stretch}.live-toolbar .controls{flex:1}.controls label{display:flex;align-items:center;gap:6px}.controls select{max-width:100%}#plot{height:340px}.panel-body{padding:0 12px 12px}summary{padding:14px 12px}summary .muted{display:block;margin:4px 0 0}header .muted{display:none}#status{max-width:55%;text-align:center}#caption{font-size:10px}}
#beat-dialog{width:min(1100px,calc(100vw - 28px))}#beat-dialog h2{margin:0;font-size:22px}.beat-heading{display:flex;justify-content:space-between;align-items:center;gap:16px}#beat-dialog #beat-overlay{height:clamp(260px,48vh,520px)}.beat-legend{font-size:13px;line-height:1.6;color:#9eb1c2}#beat-dialog .controls{justify-content:space-between}
.archive-preview{display:block;width:100%;padding:0;border:0;background:transparent;cursor:zoom-in}.archive-preview img{margin:12px 0}#archive-viewer{width:calc(100vw - 24px);max-width:1600px;max-height:calc(100dvh - 24px);padding:16px}#archive-viewport{height:68vh;overflow:auto;background:#fffafa;border-radius:8px;cursor:grab;overscroll-behavior:contain;scrollbar-gutter:stable}#archive-large{display:block;max-width:none;height:auto;user-select:none}#archive-viewer .controls{margin:0 0 12px}#archive-zoom{width:130px}.measure-fields{display:grid;grid-template-columns:repeat(3,minmax(0,1fr));gap:8px;margin:12px 0}.measure-fields label{display:flex;flex-direction:column;gap:4px}.measure-fields input{width:100%;padding:7px;border:1px solid #587184;border-radius:6px;background:#203340;color:inherit}.measure-results{font-size:13px;line-height:1.7}#beat-overlay.measuring{touch-action:none;cursor:col-resize}@media(max-width:600px){.measure-fields{grid-template-columns:repeat(2,minmax(0,1fr))}#archive-viewer{padding:10px}#archive-viewport{height:62vh}}
.language-picker{display:flex;align-items:center;gap:8px;margin-left:auto;font-size:12px}header{flex-wrap:wrap}.language-picker select{max-width:140px}
</style>
</head>
<body>
<header><div><h1>HeartMonitor</h1><div class="muted"><span data-i18n="s2">ECG · local on your ESP32</span></div></div><label class="language-picker"><span data-i18n="language">Language</span> <select id="language"><option value="en">English</option><option value="de">Deutsch</option><option value="fr">Français</option><option value="es">Español</option></select></label><span id="status" role="status" aria-live="polite"><span data-i18n="s3">Connecting …</span></span></header>
<main>
<div class="monitor-top"><div class="readout"><div><div class="muted"><span data-i18n="s4">Heart rate · estimated</span></div><strong><span id="pulse-trend" title="Trend not yet available" data-i18n-title="s5">—</span> <span id="pulse-value">—</span></strong> <span>/min</span><div id="pulse-note" class="muted"><span data-i18n="s8">Waiting for a clear beat sequence …</span></div></div></div><div class="contact-panel"><div class="contact-row"><p id="contact-status" role="status" aria-live="polite"><span data-i18n="s9">Electrode status: waiting for data …</span></p><button id="electrode-help-open" class="help-icon" type="button" aria-label="Electrode placement help" data-i18n-aria-label="s10" aria-haspopup="dialog" aria-controls="electrode-help" title="Position the electrodes" data-i18n-title="s11">?</button></div>
<div class="lead-status"><span id="lead-minus"><span data-i18n="s13">Red: –</span></span><span id="lead-plus"><span data-i18n="s14">Green: –</span></span><span id="lead-yellow" title="Derived from Red and Green, not measured separately" data-i18n-title="s15"><span data-i18n="s16">Yellow: – · derived</span></span></div></div></div>
<canvas id="plot" role="img" aria-label="Live waveform of recent sensor measurements" data-i18n-aria-label="s18"></canvas>
<div class="muted" id="caption"><span data-i18n="s19">Loading measurements …</span></div>
<div class="live-toolbar"><div class="controls"><label><span data-i18n="s20">View:</span> <select id="view-mode"><option value="scroll" data-i18n="s21">Scrolling waveform</option><option value="sweep" data-i18n="s22">Left-to-right sweep</option></select></label><label><input id="auto-height" type="checkbox" checked> <span data-i18n="s23">Autozoom</span></label><label><input id="center" type="checkbox" checked> <span data-i18n="s24">Center</span></label></div><div class="controls"><button id="beat-open" type="button" aria-haspopup="dialog" aria-controls="beat-dialog"><span data-i18n="s25">Heartbeat samples</span></button><button id="pause" type="button"><span data-i18n="s26">Pause</span></button></div></div>
<details id="display-settings"><summary><span data-i18n="s27">Display settings</span></summary><div class="controls"><label><span data-i18n="s28">Voltage:</span> <select id="voltage-mode"><option value="ecg" data-i18n="s29">ECG · mV (estimated)</option><option value="output" data-i18n="s30">Module output · mV</option></select></label><label><span data-i18n="s31">Height:</span> <select id="gain"><option value="0.2" data-i18n="s32">0.2 mV / square</option><option value="0.1" selected data-i18n="s33">0.1 mV / square</option><option value="0.05" data-i18n="s34">0.05 mV / square</option><option value="0.02" data-i18n="s35">0.02 mV / square</option></select></label></div></details>
</main>
<details class="panel" open><summary id="archive-title"><span data-i18n="s36">Waveform archive</span> <span class="muted"><span data-i18n="s37">View and download segments</span></span></summary><div class="panel-body">
<div class="controls archive-toolbar"><label><span data-i18n="s38">Segment:</span> <select id="segment-length"><option value="25" data-i18n="s39">25 large squares · approx. 5 s</option><option value="50" data-i18n="s40">50 large squares · approx. 10 s</option><option value="100" data-i18n="s41">100 large squares · approx. 20 s</option></select></label><button id="finish" type="button"><span data-i18n="s42">Save segment now</span></button></div>
<p class="muted" id="archive-progress" role="status"><span data-i18n="s43">Waiting for measurements …</span></p>
<details class="archive-info"><summary><span data-i18n="s44">Archive notes</span></summary><p class="muted" id="archive-note"><span data-i18n="s45">Up to 20 images remain in this open page. Reloading or closing discards them. Only segments with at least 0.5 s of a continuous visible trace are saved. Download important segments as SVG. Archiving requires an open, active page; Pause stops only live playback.</span></p>
</details><div id="archive-list"></div>
</div></details>
<footer class="muted"><span data-i18n="s46">Fully local · No medical diagnosis</span><details><summary><span data-i18n="s47">Measurement and accuracy</span></summary><p><span data-i18n="s48">ECG grid: small square 0.04 s · large square 0.20 s (nominal). ECG mV estimated from calibrated output mV, nominal gain 1100 and reference 1650 mV. Filters and component tolerances affect amplitude. Centering shifts the visible zero line. C3 ADC range: up to approx. 2500 mV; higher signals may clip. Screen squares are not physical millimeters.</span><br><span data-i18n="s49">The main waveform has no digital filtering. Heart rate and trend are experimental estimates, not a diagnosis. Network activity can extend sampling intervals; the time axis uses the target interval.</span></p></details></footer>
<dialog id="archive-viewer" aria-labelledby="archive-viewer-title">
<div class="beat-heading"><h2 id="archive-viewer-title"><span data-i18n="s50">Archive · enlarged view</span></h2><button id="archive-close" class="help-close" type="button" aria-label="Close archive view" data-i18n-aria-label="s51" autofocus>×</button></div>
<div class="controls"><button id="archive-zoom-out" type="button" aria-label="Zoom out" data-i18n-aria-label="s53">−</button><label>Zoom <input id="archive-zoom" type="range" min="100" max="400" step="25" value="100"></label><output id="archive-zoom-label">100 %</output><button id="archive-zoom-in" type="button" aria-label="Zoom in" data-i18n-aria-label="s57">+</button><button id="archive-fit" type="button"><span data-i18n="s59">Fit to width</span></button></div>
<p class="beat-legend"><span data-i18n="s60">Scroll or drag to move the image. Ctrl + mouse wheel zooms. On touchscreens, scroll with your finger.</span></p>
<div id="archive-viewport" tabindex="0" aria-label="Enlarged archive image, scrollable" data-i18n-aria-label="s61"><img id="archive-large" alt="Enlarged archived ECG waveform" data-i18n-alt="s62" draggable="false"></div>
</dialog>
<dialog id="beat-dialog" aria-labelledby="beat-title" aria-describedby="beat-description">
<div class="beat-heading"><h2 id="beat-title"><span data-i18n="s25">Heartbeat samples</span></h2><button id="beat-close" class="help-close" type="button" aria-label="Close heartbeat samples" data-i18n-aria-label="s63" autofocus>×</button></div>
<p id="beat-description" class="beat-legend"><span data-i18n="s64">Up to 100 detected beats, aligned at the peak. Shared time and amplitude scales; only the baseline is subtracted per beat.</span></p>
<canvas id="beat-overlay" role="img" aria-label="Individual beats, mean and variability band of plus or minus one standard deviation" data-i18n-aria-label="s65"></canvas>
<div class="controls"><label><input id="beat-smoothing" type="checkbox"> <span data-i18n="s66">Smooth display</span></label><label><input id="beat-mean" type="checkbox" checked> <span data-i18n="s67">Mean</span></label><label><input id="beat-median" type="checkbox" checked> <span data-i18n="s68">Median</span></label><label><input id="beat-reference" type="checkbox" checked> <span data-i18n="s69">Example waveform</span></label><span class="beat-legend"><span data-i18n="s70">Time: fine 20 ms · bold 100 ms</span></span></div>
<p class="beat-legend"><span data-i18n="s71">Blue-gray: schematic example with P wave, PR segment, QRS complex, ST segment and T wave. Height fitted to the view; sections are not measured boundaries or normal ranges.</span></p>
<details class="archive-info"><summary><span data-i18n="s72">Measure intervals on the mean waveform</span></summary>
<label><input id="beat-measure" type="checkbox"> <span data-i18n="s73">Show and move measurement markers</span></label>
<p class="beat-legend"><span data-i18n="s74">Drag lines with a mouse or finger, or enter positions below in ms. Initial positions are illustrative: place boundaries yourself on the dark mean waveform. The mean continues to update. The example waveform can remain visible; shaded sections follow the markers.</span></p>
<div class="measure-fields">
<label><span data-i18n="s75">P start (ms)</span><input id="measure-0" type="number" min="-250" max="450" step="1" value="-220"></label>
<label><span data-i18n="s76">P end (ms)</span><input id="measure-1" type="number" min="-250" max="450" step="1" value="-120"></label>
<label><span data-i18n="s77">QRS start (ms)</span><input id="measure-2" type="number" min="-250" max="450" step="1" value="-40"></label>
<label><span data-i18n="s78">QRS end (ms)</span><input id="measure-3" type="number" min="-250" max="450" step="1" value="40"></label>
<label><span data-i18n="s79">T start (ms)</span><input id="measure-4" type="number" min="-250" max="450" step="1" value="140"></label>
<label><span data-i18n="s80">T end (ms)</span><input id="measure-5" type="number" min="-250" max="450" step="1" value="360"></label>
</div><p id="measure-results" class="measure-results" role="status"><span data-i18n="s81">Interval measurement is off.</span></p>
<button id="measure-reset" type="button"><span data-i18n="s82">Reset markers</span></button>
<p class="beat-legend"><span data-i18n="s83">Intervals are calculated from your markers, not automatically detected as medical waves. Requires a visible mean waveform. Marker resolution: 1 ms; no automatic evaluation of intervals.</span></p>
</details>
<p id="overlay-note" class="beat-legend"><span data-i18n="s84">Waiting for a sufficiently clear beat sequence …</span></p>
<div class="controls"><span class="beat-legend"><span data-i18n="s85">Dashed turquoise: individual beats · Dark: mean · Purple: median · Band: ±1 standard deviation</span></span><button id="clear-beats" type="button"><span data-i18n="s86">Clear samples</span></button></div>
<p class="beat-legend"><span data-i18n="s87">The band shows waveform variability, not heart rate variability (HRV). Short timing gaps are connected visually with 90% black lines; these are not measured intermediate values. Mean, median and variability include all collected samples, including clipped waveforms. Measurements are not reconstructed. Interference and movement can increase variability. Experimental detection, no medical analysis. Samples remain in the browser until cleared or reloaded; at most the latest 100.</span></p>
</dialog>
<dialog id="electrode-help" aria-labelledby="electrode-help-title" aria-describedby="electrode-help-description">
<div class="help-heading"><h2 id="electrode-help-title" class="sr-only"><span data-i18n="s88">Electrode placement, front view</span></h2><button id="electrode-help-close" class="help-close" type="button" aria-label="Close help" data-i18n-aria-label="s89" autofocus>×</button></div>
<p id="electrode-help-description" class="sr-only"><span data-i18n="s90">Front view: the body's right side is on the left of the image. RA red, LA yellow, RL green. Left: RA on the right forearm, LA on the left forearm, RL on the right leg. Right: RA and LA on the right and left upper chest, RL on the lower right abdomen. Cable colors may vary; follow the labels. Use ECG gel pads. While attached to the body, use battery power only, with no USB connection.</span></p>
<svg width="0" height="0" aria-hidden="true" style="position:absolute"><defs><g id="commons-front-body"><g class="commons-front" transform="translate(-63.131355,439.78744)"><g transform="matrix(1.6534106,0,0,1.6534106,-47.03879,-255.5683)" fill="none" stroke="#8397a7" stroke-width="1.3" stroke-linecap="round" stroke-linejoin="round"><path d="m 151.25027,121.09597 c 0,0 0.12338,1.67247 0.15689,2.51015 0.0397,0.99296 0.0519,1.98705 0.0523,2.9808 4.6e-4,1.04604 0.006,2.09328 -0.0523,3.13769 -0.0205,0.36715 -0.0127,0.74214 -0.10459,1.0982 -0.10924,0.42332 -0.33572,0.80772 -0.52295,1.20278 -0.29382,0.61996 -0.55632,1.26246 -0.94131,1.83032 -0.40212,0.59314 -0.89103,1.12904 -1.41196,1.62113 -0.78575,0.74226 -1.66661,1.38238 -2.56245,1.98721 -1.40494,0.94855 -2.92105,1.7212 -4.39276,2.56244 -1.30088,0.7436 -2.5848,1.52049 -3.92211,2.19639 -1.09313,0.55248 -2.23301,1.00716 -3.34687,1.51655 -1.13487,0.519 -2.26035,1.05855 -3.39916,1.56884 -0.79792,0.35754 -1.61513,0.67209 -2.40557,1.0459 -0.72591,0.34329 -1.39594,0.8065 -2.14408,1.09819 -1.09539,0.42707 -2.2674,0.62293 -3.39917,0.94131 -1.09946,0.30929 -2.23226,0.52183 -3.29457,0.9413 -0.71062,0.2806 -1.37594,0.66721 -2.0395,1.0459 -0.68045,0.38832 -1.37524,0.7659 -1.9872,1.25508 -0.53917,0.43099 -1.0029,0.95082 -1.46426,1.46425 -0.464,0.51636 -0.94232,1.03067 -1.30737,1.62114 -0.35276,0.57059 -0.62853,1.19261 -0.83672,1.83032 -0.21537,0.65972 -0.32494,1.35183 -0.41835,2.0395 -0.13874,1.02144 -0.15742,2.05587 -0.20918,3.08539 -0.0534,1.06256 -0.0545,2.12727 -0.10459,3.18999 -0.0535,1.13394 -0.11019,2.26829 -0.20918,3.39916 -0.0673,0.76899 -0.21783,1.53028 -0.26148,2.30097 -0.0493,0.87019 -0.0482,1.74449 0,2.61474 0.0437,0.78804 0.16543,1.56989 0.26148,2.35327 0.17552,1.43147 0.37739,2.85961 0.57524,4.28817 0.11837,0.85466 0.219,1.71225 0.36606,2.56245 0.17888,1.03417 0.45258,2.05056 0.62754,3.0854 0.1085,0.64172 0.22592,1.28504 0.26148,1.9349 0.0381,0.69644 0.003,1.39648 -0.0523,2.0918 -0.0623,0.78891 -0.19324,1.57113 -0.31377,2.35326 -0.21562,1.39921 -0.47127,2.79211 -0.73213,4.18359 -0.1474,0.78626 -0.34591,1.5631 -0.47065,2.35327 -0.11767,0.74538 -0.18803,1.49765 -0.26147,2.24867 -0.10722,1.09642 -0.14762,2.19883 -0.26148,3.29458 -0.12715,1.22367 -0.29966,2.44232 -0.47065,3.66064 -0.22547,1.60642 -0.50429,3.20503 -0.73213,4.81112 -0.18768,1.32298 -0.28629,2.65931 -0.52295,3.97441 -0.15203,0.84484 -0.34904,1.68208 -0.57524,2.51015 -0.2121,0.77643 -0.47375,1.53869 -0.73213,2.30097 -0.29737,0.87731 -0.58572,1.75936 -0.9413,2.61474 -0.42202,1.01521 -0.89813,2.00883 -1.41196,2.98081 -0.27386,0.51804 -0.61735,0.99736 -0.88902,1.51655 -0.3652,0.69793 -0.68385,1.41983 -0.9936,2.14408 -0.20621,0.48215 -0.41544,0.9648 -0.57524,1.46426 -0.19711,0.61608 -0.33371,1.25042 -0.47065,1.88261 -0.18385,0.84876 -0.30122,1.7107 -0.47066,2.56245 -0.19479,0.97914 -0.41964,1.95207 -0.62754,2.92851 -0.19294,0.90619 -0.4114,1.80743 -0.57524,2.71933 -0.0841,0.46829 -0.15153,0.93968 -0.20918,1.41196 -0.11034,0.90391 -0.20132,1.81069 -0.26147,2.71933 -0.0634,0.95728 -0.0872,1.917 -0.10459,2.87622 -0.013,0.71458 0.0149,1.42954 0,2.14408 -0.0174,0.83726 -0.0339,1.67571 -0.10459,2.51016 -0.0579,0.68294 -0.1323,1.36638 -0.26147,2.03949 -0.11873,0.61867 -0.31693,1.21941 -0.47066,1.83032 -0.28476,1.1316 -0.53855,2.27103 -0.83672,3.39917 -0.42584,1.61119 -0.85811,3.22187 -1.35966,4.81112 -0.35008,1.10929 -0.69772,2.22308 -1.15049,3.29457 -0.25792,0.61037 -0.70134,1.14253 -0.88901,1.77803 -0.13412,0.45416 -0.0362,0.95406 -0.15688,1.41196 -0.13537,0.51347 -0.30898,1.0394 -0.62754,1.46425 -0.2303,0.30714 -0.5458,0.56014 -0.88901,0.73213 -0.7862,0.39398 -1.74015,0.31584 -2.56245,0.62754 -0.69994,0.26532 -1.32121,0.70418 -1.9872,1.04589 -0.83231,0.42705 -1.6559,0.8738 -2.51015,1.25508 -0.65031,0.29026 -1.31007,0.56391 -1.98721,0.78442 -0.46232,0.15055 -1.00127,0.1058 -1.41196,0.36607 -0.22999,0.14576 -0.34532,0.42116 -0.52295,0.62753 -0.27386,0.31818 -0.5776,0.61101 -0.83671,0.94131 -0.37902,0.48316 -0.72932,0.99037 -1.0459,1.51655 -0.25323,0.42088 -0.40773,0.89844 -0.67983,1.30737 -0.30168,0.45338 -0.70436,0.83091 -1.0459,1.25508 -0.24929,0.30961 -0.44656,0.66479 -0.73213,0.9413 -0.17033,0.16493 -0.39499,0.26434 -0.57524,0.41836 -0.075,0.0641 -0.14933,0.13082 -0.20918,0.20918 -0.17061,0.22337 -0.27059,0.49303 -0.41836,0.73213 -0.16521,0.26732 -0.35992,0.51576 -0.52295,0.78442 -0.20641,0.34015 -0.33152,0.7314 -0.57524,1.0459 -0.24927,0.32167 -0.58766,0.56324 -0.88901,0.83672 -0.27443,0.24906 -0.54382,0.50506 -0.83672,0.73212 -0.31717,0.24587 -0.67643,0.43397 -0.9936,0.67984 -0.14645,0.11353 -0.32175,0.20794 -0.41836,0.36606 -0.11242,0.18399 -0.18041,0.41321 -0.15688,0.62754 0.0213,0.19373 0.13659,0.37332 0.26147,0.52295 0.16754,0.20075 0.40076,0.3405 0.62754,0.47065 0.31168,0.17887 0.64135,0.34723 0.9936,0.41836 0.27339,0.0552 0.55928,0.0286 0.83672,0 0.42509,-0.0438 0.84485,-0.14175 1.25507,-0.26148 0.51901,-0.15148 1.03457,-0.33028 1.51655,-0.57524 0.42671,-0.21687 0.84011,-0.47204 1.20278,-0.78442 0.31809,-0.27397 0.55368,-0.63126 0.83672,-0.94131 0.25775,-0.28235 0.58129,-0.51284 0.78442,-0.83672 0.129,-0.20569 0.14642,-0.46603 0.26148,-0.67983 0.0711,-0.13204 0.16859,-0.24834 0.26147,-0.36606 0.3291,-0.41711 0.67881,-0.81868 1.0459,-1.20278 0.34927,-0.36545 0.70076,-0.7335 1.09819,-1.0459 0.39743,-0.3124 0.55728,-0.43262 0.88901,-0.52295 0.23547,-0.0641 0.49124,-0.0391 0.73213,0 0.32647,0.053 0.64243,0.17214 0.94131,0.31377 0.35399,0.16775 0.9936,0.62754 0.9936,0.62754"/><path d="m 88.49648,286.29532 c 0,0 2.10956,-0.30392 3.13769,-0.57525 1.23131,-0.32496 2.41752,-0.49004 3.60835,-0.9413 0.98682,-0.37395 2.09272,-0.87226 2.92851,-1.51655 0.77865,-0.60024 1.27717,-1.50726 1.77802,-2.35327 0.47698,-0.80569 1.15049,-2.56245 1.15049,-2.56245"/><path d="m 84.10372,285.82466 c 0,0 5.8e-4,0.666 0.0523,0.9936 0.0844,0.5346 0.32048,1.03655 0.41836,1.56885 0.0919,0.49984 0.15445,1.00834 0.15689,1.51655 0.003,0.56025 -0.068,1.12027 -0.15689,1.67343 -0.13623,0.84753 -0.35592,1.68024 -0.57524,2.51015 -0.093,0.3519 -0.26091,0.68577 -0.31377,1.0459 -0.0481,0.32769 0.0311,0.66387 0,0.9936 -0.035,0.371 -0.1109,0.73874 -0.20918,1.09819 -0.12215,0.44677 -0.30309,0.87557 -0.47065,1.30737 -0.16397,0.42252 -0.35484,0.83419 -0.52295,1.25508 -0.23535,0.58926 -0.45633,1.18417 -0.67983,1.77802 -0.17678,0.46973 -0.31211,0.9565 -0.52295,1.41196 -0.13443,0.2904 -0.35235,0.53939 -0.47066,0.83672 -0.10629,0.26712 -0.15184,0.55501 -0.20918,0.83672 -0.0669,0.32857 -0.0736,0.66881 -0.15688,0.9936 -0.11507,0.44865 -0.31248,0.87204 -0.47065,1.30737 -0.19021,0.52351 -0.38827,1.04418 -0.57525,1.56885 -0.161,0.45177 -0.33033,0.90104 -0.47065,1.35966 -0.0792,0.25877 -0.14873,0.52065 -0.20918,0.78442 -0.1031,0.44986 -0.19325,0.90321 -0.26147,1.35967 -0.0726,0.48548 -0.15785,0.97337 -0.15689,1.46425 6.2e-4,0.3157 -0.0134,0.6485 0.10459,0.94131 0.10689,0.26517 0.32183,0.47663 0.52295,0.67983 0.21833,0.22058 0.43611,0.48198 0.73213,0.57525 0.29972,0.0944 0.64934,0.0639 0.9413,-0.0523 0.2758,-0.1098 0.48687,-0.34967 0.67984,-0.57524 0.30511,-0.35666 0.52318,-0.7825 0.73213,-1.20278 0.31703,-0.63768 0.5546,-1.31317 0.78442,-1.98721 0.26349,-0.77281 0.42847,-1.57642 0.67983,-2.35326 0.22237,-0.68723 0.43373,-1.38171 0.73213,-2.0395 0.14828,-0.32688 0.34586,-0.62909 0.52295,-0.94131 0.18881,-0.33288 0.41805,-0.64467 0.57524,-0.9936 0.15849,-0.35181 0.23237,-0.73623 0.36606,-1.09819 0.20861,-0.56479 0.45473,-1.11502 0.67984,-1.67344 0.21058,-0.52238 0.29444,-1.11466 0.62753,-1.56884 0.14652,-0.19978 0.35384,-0.35947 0.57525,-0.47065 0.12846,-0.0645 0.27547,-0.12027 0.41835,-0.10459 0.15498,0.017 0.32241,0.0863 0.41836,0.20918 0.0989,0.12667 0.10029,0.31 0.10459,0.47065 0.006,0.21199 -0.039,0.42587 -0.10459,0.62754 -0.10848,0.33361 -0.33136,0.61934 -0.47065,0.9413 -0.14015,0.32395 -0.24603,0.66168 -0.36606,0.99361 -0.19499,0.53922 -0.33933,1.09853 -0.57525,1.62114 -0.14768,0.32715 -0.36404,0.61945 -0.52294,0.9413 -0.19354,0.39201 -0.38487,0.78798 -0.52295,1.20278 -0.215,0.64588 -0.31966,1.32344 -0.47066,1.98721 -0.21768,0.95684 -0.41487,1.91824 -0.62753,2.87621 -0.12006,0.54082 -0.2639,1.07666 -0.36607,1.62114 -0.13003,0.69297 -0.24962,1.38965 -0.31377,2.09179 -0.0476,0.52107 -0.0845,1.0466 -0.0523,1.56885 0.0206,0.33467 0.0406,0.6791 0.15688,0.9936 0.0923,0.24957 0.22486,0.49719 0.41836,0.67983 0.18717,0.17667 0.44105,0.27002 0.67983,0.36607 0.30212,0.12153 0.61886,0.30703 0.94131,0.26147 0.26346,-0.0372 0.47103,-0.25343 0.67983,-0.41836 0.19345,-0.1528 0.41015,-0.30375 0.52295,-0.52295 0.19407,-0.37712 0.13029,-0.83834 0.20918,-1.25507 0.10937,-0.57778 0.18838,-1.16517 0.36606,-1.72573 0.0802,-0.2531 0.25357,-0.47353 0.31377,-0.73213 0.0752,-0.32302 0.009,-0.66482 0.0523,-0.9936 0.0656,-0.49483 0.18416,-0.98221 0.31377,-1.46425 0.19037,-0.70802 0.42617,-1.40391 0.67983,-2.0918 0.18928,-0.5133 0.36654,-1.03573 0.62754,-1.51655 0.16147,-0.29746 0.44623,-0.5238 0.57524,-0.83671 0.0743,-0.18018 0.0723,-0.38304 0.10459,-0.57525 0.0379,-0.22611 0.0604,-0.45486 0.10459,-0.67983 0.0864,-0.43975 0.23238,-0.86666 0.31377,-1.30737 0.0734,-0.3976 0.0741,-0.80702 0.15688,-1.20278 0.11517,-0.55078 0.27376,-1.09402 0.47066,-1.62114 0.0873,-0.2338 0.1113,-0.5339 0.31377,-0.67983 0.12805,-0.0923 0.32422,-0.11124 0.47065,-0.0523 0.1263,0.0508 0.21512,0.18576 0.26147,0.31377 0.0653,0.18029 0.0266,0.38535 0,0.57524 -0.0528,0.37703 -0.20605,0.73304 -0.31377,1.09819 -0.11858,0.40196 -0.2704,0.79477 -0.36606,1.20279 -0.0726,0.3097 -0.12045,0.6253 -0.15688,0.9413 -0.062,0.53794 -0.0729,1.08056 -0.10459,1.62114 -0.0194,0.33109 -0.0109,0.66453 -0.0523,0.9936 -0.0886,0.70553 -0.2758,1.39516 -0.41836,2.0918 -0.15354,0.75025 -0.33604,1.4948 -0.47065,2.24867 -0.0836,0.46838 -0.12019,0.94457 -0.20918,1.41196 -0.10044,0.52752 -0.27677,1.03933 -0.36606,1.56885 -0.0554,0.32839 -0.10555,0.66057 -0.10459,0.9936 9.1e-4,0.3157 -0.0254,0.6536 0.10459,0.94131 0.10667,0.23617 0.31353,0.42261 0.52295,0.57524 0.17022,0.12405 0.36939,0.21688 0.57524,0.26147 0.27259,0.059 0.56141,0.0447 0.83672,0 0.21764,-0.0353 0.43997,-0.0933 0.62753,-0.20918 0.23067,-0.14256 0.42322,-0.35069 0.57525,-0.57524 0.14885,-0.21986 0.22967,-0.48029 0.31377,-0.73213 0.25579,-0.76593 0.40199,-1.56455 0.57524,-2.35326 0.15622,-0.71122 0.27723,-1.42972 0.41836,-2.14409 0.22395,-1.13358 0.42633,-2.27182 0.67983,-3.39916 0.0788,-0.35061 0.1295,-0.71165 0.26147,-1.0459 0.13182,-0.33386 0.41572,-0.59876 0.52295,-0.94131 0.10467,-0.33437 0.0871,-0.69596 0.10459,-1.04589 0.0243,-0.48748 -0.0303,-0.97712 0,-1.46426 0.0437,-0.70133 0.17043,-1.39502 0.26148,-2.09179 0.0502,-0.38378 0.0837,-0.77043 0.15688,-1.15049 0.0408,-0.21173 0.0507,-0.43991 0.15688,-0.62754 0.0486,-0.0858 0.12098,-0.16508 0.20918,-0.20918 0.11025,-0.0551 0.26122,-0.1171 0.36607,-0.0523 0.0469,0.029 0.0495,0.10183 0.0523,0.15688 0.008,0.1605 -0.0833,0.31137 -0.10459,0.47066 -0.0486,0.36324 -0.0344,0.73215 -0.0523,1.09819 -0.017,0.34865 -0.0683,0.6972 -0.0523,1.0459 0.017,0.36939 0.0897,0.73456 0.15689,1.09819 0.0714,0.38673 0.21762,0.75966 0.26147,1.15048 0.0758,0.67559 0,1.35967 0,2.0395 0,0.92388 -0.0125,1.84784 0,2.77163 0.009,0.64515 -0.12172,1.31361 0.0523,1.93491 0.0758,0.27066 0.22287,0.53017 0.41836,0.73212 0.18507,0.19118 0.42121,0.35577 0.67983,0.41836 0.2209,0.0535 0.46655,0.0262 0.67983,-0.0523 0.22249,-0.0819 0.41762,-0.24124 0.57524,-0.41836 0.21273,-0.23906 0.34679,-0.54166 0.47066,-0.83672 0.21781,-0.51883 0.34574,-1.07249 0.47065,-1.62114 0.0941,-0.41355 0.1742,-0.83239 0.20918,-1.25507 0.0273,-0.33007 0.003,-0.66242 0,-0.99361 -0.009,-0.99371 -0.1029,-1.98834 -0.0523,-2.9808 0.0223,-0.43835 0.12075,-0.86994 0.15689,-1.30737 0.0316,-0.38259 0.0436,-0.7667 0.0523,-1.15049 0.0139,-0.60995 -0.0326,-1.22108 0,-1.83032 0.0262,-0.49018 0.063,-0.98244 0.15689,-1.46425 0.0486,-0.24912 0.12602,-0.49233 0.20918,-0.73213 0.24076,-0.69426 0.56204,-1.35795 0.83672,-2.0395 0.33638,-0.83465 0.64959,-1.67862 0.9936,-2.51015 0.31938,-0.77199 0.63112,-1.54826 0.9936,-2.30097 0.38572,-0.80097 0.88902,-1.5431 1.25506,-2.35325 0.36794,-0.81435 0.69867,-1.65011 0.94131,-2.51015 0.14945,-0.52973 0.23208,-1.07683 0.31377,-1.62114 0.1457,-0.97088 0.2448,-1.94918 0.31377,-2.92851 0.0723,-1.02651 0.0872,-2.05648 0.10459,-3.08539 0.009,-0.5403 0.0964,-1.08944 0,-1.62115 -0.0532,-0.29309 -0.31378,-0.83672 -0.31378,-0.83672"/><path d="m 107.58409,278.66027 c 0,0 0.12381,-0.68001 0.26148,-0.9936 0.32461,-0.7394 0.91452,-1.33398 1.30737,-2.0395 0.43241,-0.77657 0.79534,-1.59075 1.15048,-2.40556 0.56908,-1.30565 1.10749,-2.62692 1.56885,-3.97441 0.42349,-1.23688 0.68989,-2.52324 1.09819,-3.76522 0.52186,-1.5874 1.16003,-3.13423 1.72573,-4.70654 0.31916,-0.88709 0.58651,-1.79359 0.94131,-2.66703 0.46965,-1.15617 1.04438,-2.26681 1.56884,-3.39917 0.57359,-1.23841 1.18586,-2.45945 1.72573,-3.71293 0.57877,-1.34378 1.02764,-2.74167 1.62114,-4.079 0.48067,-1.08309 1.05134,-2.12399 1.56884,-3.18998 0.4052,-0.83466 0.89099,-1.6363 1.20279,-2.51015 0.22307,-0.62517 0.34874,-1.28243 0.47065,-1.93491 0.12271,-0.65674 0.18763,-1.32318 0.26147,-1.9872 0.0851,-0.76544 0.20918,-2.30098 0.20918,-2.30098"/><path d="m 124.05696,236.82441 c 0,0 0.55941,-0.91072 0.73213,-1.41196 0.1849,-0.53657 0.28691,-1.10654 0.31377,-1.67343 0.0273,-0.57697 -0.2014,-1.14983 -0.15688,-1.72573 0.0388,-0.50161 0.27895,-0.96875 0.36606,-1.46426 0.088,-0.50054 0.13889,-1.00865 0.15688,-1.51655 0.0191,-0.54032 0.004,-1.08343 -0.0523,-1.62114 -0.0517,-0.4931 -0.2028,-0.97193 -0.26148,-1.46425 -0.0682,-0.57225 -0.14562,-1.15089 -0.10459,-1.72573 0.0431,-0.60357 0.2553,-1.18314 0.36607,-1.77802 0.17469,-0.93816 0.30576,-1.88398 0.47065,-2.82392 0.23276,-1.32683 0.47933,-2.65125 0.73213,-3.97441 0.32013,-1.67559 0.66443,-3.34647 0.9936,-5.0203 0.29817,-1.51619 0.64487,-3.02383 0.88901,-4.54965 0.17764,-1.11018 0.27715,-2.23147 0.41836,-3.34687 0.0861,-0.67997 0.26148,-2.0395 0.26148,-2.0395"/><path d="m 126.14876,175.22111 c 0,0 0.37352,1.16883 0.62753,1.72573 0.44687,0.97972 1.01594,1.89989 1.56885,2.82392 0.4469,0.74686 0.86162,1.5221 1.41196,2.19638 0.63136,0.77354 1.49873,1.3299 2.14409,2.0918 0.63133,0.74534 1.67343,2.40556 1.67343,2.40556"/><path d="m 128.60661,180.24141 c 0,0 0.75081,1.39473 0.9936,2.14409 0.22444,0.69272 0.36963,1.41755 0.41836,2.14409 0.0596,0.88855 -0.10111,1.77823 -0.15688,2.66703 -0.0656,1.04616 -0.14814,2.09125 -0.20918,3.13769 -0.0813,1.3939 -0.13411,2.78934 -0.20918,4.18359 -0.0488,0.90664 -0.13072,1.81176 -0.15688,2.71933 -0.0251,0.87122 0,1.74316 0,2.61474 0,0.67983 -0.0117,1.35977 0,2.0395 0.0174,1.01148 0.0948,2.02151 0.10459,3.0331 0.0111,1.15057 -0.0969,2.30171 -0.0523,3.45146 0.0292,0.75223 0.13275,1.49977 0.20918,2.24868 0.0962,0.94221 0.2269,1.88081 0.31377,2.82392 0.0657,0.71358 0.11936,1.42846 0.15688,2.14408 0.0575,1.09724 0.029,2.19844 0.10459,3.29458 0.0567,0.82195 0.1692,1.63913 0.26148,2.45785 0.0826,0.73266 0.20964,1.46091 0.26147,2.19639 0.0552,0.78267 0.0934,1.56972 0.0523,2.35326 -0.0432,0.8248 -0.19356,1.64072 -0.31377,2.45786 -0.18519,1.25884 -0.41287,2.51108 -0.62754,3.76523 -0.22096,1.29092 -0.46751,2.57745 -0.67983,3.86982 -0.243,1.47909 -0.47017,2.96088 -0.67984,4.44506 -0.13277,0.93985 -0.2595,1.88074 -0.36606,2.82392 -0.16318,1.44434 -0.34855,2.88862 -0.41836,4.34047 -0.0301,0.62681 -0.0112,1.25517 0,1.88261 0.009,0.48832 0.0436,0.97593 0.0523,1.46425 0.009,0.48801 0.0438,0.97815 0,1.46426 -0.035,0.38821 -0.11854,0.77139 -0.20918,1.15049 -0.19878,0.83143 -0.55426,1.6217 -0.73213,2.45785 -0.16826,0.79095 -0.17985,1.60808 -0.31377,2.40556 -0.20042,1.1935 -0.47707,2.37302 -0.73213,3.55605 -0.26738,1.24018 -0.58306,2.46987 -0.83671,3.71293 -0.29052,1.42377 -0.48931,2.86535 -0.78443,4.28818 -0.20352,0.98124 -0.49762,1.94309 -0.67983,2.92851 -0.20798,1.1248 -0.35531,2.26113 -0.47065,3.39916 -0.16381,1.61623 -0.23485,3.24083 -0.31377,4.86342 -0.0517,1.06265 -0.0872,2.12623 -0.10459,3.18999 -0.0157,0.95861 0.0506,1.91881 0,2.87621 -0.0611,1.15533 -0.21981,2.3038 -0.36607,3.45146 -0.20943,1.64335 -0.51109,3.27388 -0.73212,4.91571 -0.253,1.87925 -0.52524,3.75795 -0.67984,5.64784 -0.1636,1.99985 -0.20754,4.0081 -0.26147,6.01391 -0.0455,1.69035 -0.0523,3.38164 -0.0523,5.0726 0,1.69096 0.0376,3.38171 0.0523,5.0726 0.0214,2.45783 -0.0188,4.91668 0.0523,7.37357 0.0596,2.05872 0.21574,4.11353 0.31376,6.17078 0.0747,1.56862 0.0998,3.13996 0.20918,4.70654 0.0512,0.73365 0.13542,1.46465 0.20918,2.19638 0.16528,1.63951 0.3379,3.27832 0.52295,4.91571 0.23067,2.04106 0.44891,4.08407 0.73213,6.1185 0.26041,1.87053 0.5389,3.7397 0.88901,5.59554 0.21171,1.12221 0.5468,2.22001 0.73213,3.34687 0.10247,0.62303 0.13813,1.25523 0.20918,1.88262 0.0513,0.45333 0.13759,0.90384 0.15688,1.35966 0.0243,0.57499 -0.0436,1.15029 -0.0523,1.72573 -0.0166,1.09807 0.0361,2.19698 0,3.29458 -0.0436,1.32695 -0.16425,2.6503 -0.26148,3.9744 -0.0948,1.2907 -0.22557,2.57866 -0.31377,3.86982 -0.0642,0.94057 -0.1512,1.88118 -0.15688,2.82392 -0.005,0.8026 0.0742,1.60352 0.10459,2.40556 0.0409,1.08055 0.074,2.16139 0.10459,3.24228 0.0202,0.71462 0.0943,1.43041 0.0523,2.14409 -0.029,0.49219 -0.12077,0.9792 -0.20918,1.46425 -0.20172,1.10675 -0.4598,2.20306 -0.73212,3.29458 -0.36343,1.4567 -0.81626,2.88973 -1.20278,4.34047 -0.39838,1.49523 -0.78291,2.99425 -1.15049,4.49735 -0.38268,1.56488 -0.7535,3.13286 -1.09819,4.70654 -0.31599,1.44266 -0.67559,2.87911 -0.88901,4.34047 -0.086,0.58873 -0.11241,1.18471 -0.15689,1.77802 -0.10576,1.41069 -0.20063,2.82254 -0.26147,4.23588 -0.0615,1.4285 -0.11963,2.85844 -0.10459,4.28818 0.008,0.76774 0.0558,1.53474 0.10459,2.30097 0.0678,1.06474 0.13008,2.13121 0.26147,3.18998 0.13058,1.05225 0.37451,2.08781 0.52295,3.13769 0.21128,1.49436 0.36162,2.99679 0.52295,4.49736 0.15167,1.4107 0.21977,2.83102 0.41836,4.23588 0.25555,1.80778 0.69513,3.58518 0.9936,5.38637 0.29379,1.77297 0.47736,3.56335 0.78442,5.33407 0.12149,0.70062 0.26403,1.39767 0.41836,2.09179 0.19087,0.85843 0.41631,1.70881 0.62754,2.56245 0.37981,1.5349 0.84477,3.05058 1.15048,4.60194 0.21115,1.07148 0.35323,2.15652 0.47066,3.24228 0.10523,0.97298 0.16411,1.95089 0.20918,2.92851 0.0385,0.83601 0.0687,1.67341 0.0523,2.51015 -0.0171,0.87298 -0.15688,2.61474 -0.15688,2.61474"/><path d="m 125.05056,464.56837 c 0,0 -0.41632,1.17571 -0.57524,1.77802 -0.15437,0.58508 -0.19587,1.19735 -0.36606,1.77803 -0.13658,0.46598 -0.35897,0.9026 -0.52295,1.35966 -0.16753,0.46697 -0.34621,0.93171 -0.47065,1.41196 -0.14236,0.54939 -0.26125,1.10834 -0.31377,1.67344 -0.0468,0.50335 -0.0518,1.0137 0,1.51655 0.0438,0.42509 0.15341,0.84162 0.26147,1.25507 0.0878,0.33603 0.24772,0.65262 0.31377,0.9936 0.0432,0.22314 0.0436,0.45272 0.0523,0.67984 0.0161,0.41805 0,1.25507 0,1.25507"/><path d="m 125.46892,474.87045 c 0,0 -0.63962,1.42646 -1.04589,2.09179 -0.33796,0.55347 -0.78504,1.03313 -1.15049,1.56885 -0.34883,0.51135 -0.76114,0.99514 -0.9936,1.56884 -0.16049,0.39606 -0.19786,0.8325 -0.26148,1.25508 -0.0834,0.55401 -0.0998,1.11609 -0.15688,1.67343 -0.0322,0.31406 0.009,0.64675 -0.10459,0.94131 -0.13926,0.36112 -0.44249,0.63557 -0.67983,0.9413 -0.16697,0.21509 -0.39358,0.38794 -0.52295,0.62754 -0.19911,0.36876 -0.18261,0.82598 -0.36606,1.20278 -0.18628,0.38262 -0.47439,0.70727 -0.73213,1.0459 -0.31496,0.41381 -0.63668,0.82456 -0.9936,1.20278 -0.45714,0.48442 -0.97995,0.90241 -1.46426,1.35967 -0.43925,0.41472 -0.85599,0.85359 -1.30737,1.25507 -0.28684,0.25513 -0.64155,0.43864 -0.88901,0.73213 -0.27178,0.32233 -0.4797,0.70335 -0.62754,1.09819 -0.12467,0.33296 -0.13945,0.69727 -0.20918,1.0459 -0.0697,0.34863 -0.20704,0.69036 -0.20918,1.04589 -0.002,0.28376 0.0946,0.55988 0.15689,0.83672 0.0752,0.33412 0.21101,0.65486 0.26147,0.9936 0.0668,0.44861 -0.12257,0.94118 0.0523,1.35967 0.1474,0.35275 0.48358,0.6008 0.78442,0.83671 0.25181,0.19747 0.53666,0.35946 0.83672,0.47066 0.33338,0.12355 0.69209,0.17415 1.04589,0.20918 0.19082,0.0189 0.57525,0 0.57525,0"/><path d="m 118.25224,494.5333 c 0,0 -0.3167,0.32421 -0.41836,0.52295 -0.14831,0.28992 -0.20064,0.62139 -0.26147,0.94131 -0.0622,0.32717 -0.0733,0.66204 -0.10459,0.9936 -0.0394,0.41795 -0.10806,0.83528 -0.10459,1.25507 0.004,0.52554 0.0319,1.05837 0.15688,1.56885 0.067,0.27354 0.14443,0.5594 0.31377,0.78442 0.11951,0.15881 0.2877,0.2884 0.47065,0.36607 0.22692,0.0963 0.48582,0.0943 0.73213,0.10458 0.29659,0.0123 0.88901,-0.0523 0.88901,-0.0523"/><path d="m 121.7037,494.84707 c 0,0 -0.18266,0.53518 -0.31377,0.78442 -0.11704,0.2225 -0.31875,0.39671 -0.41836,0.62754 -0.0922,0.21353 -0.0988,0.45464 -0.15689,0.67983 -0.0634,0.24576 -0.10004,0.50299 -0.20918,0.73213 -0.0915,0.1921 -0.2896,0.32438 -0.36606,0.52295 -0.0505,0.13115 -0.0155,0.28271 -0.0523,0.41836 -0.0694,0.25627 -0.17346,0.50672 -0.31377,0.73213 -0.0849,0.13644 -0.25801,0.21533 -0.31377,0.36606 -0.10281,0.27793 -0.0773,0.60294 0,0.88901 0.0632,0.23378 0.18096,0.47139 0.36606,0.62754 0.22768,0.19207 0.54724,0.24356 0.83672,0.31377 0.28997,0.0703 0.59114,0.0871 0.88901,0.10459 0.26103,0.0153 0.52317,0.0109 0.78442,0 0.20972,-0.009 0.62754,-0.0523 0.62754,-0.0523"/><path d="m 124.84139,495.26543 c 0,0 -0.34259,0.4718 -0.47066,0.73213 -0.11439,0.23252 -0.16681,0.49089 -0.26147,0.73212 -0.097,0.24716 -0.19436,0.49499 -0.31377,0.73213 -0.10891,0.21629 -0.27477,0.40324 -0.36606,0.62754 -0.0813,0.19971 -0.10296,0.41877 -0.15689,0.62754 -0.0677,0.26201 -0.12391,0.52759 -0.20918,0.78442 -0.0887,0.26727 -0.24907,0.51034 -0.31377,0.78442 -0.0482,0.20429 -0.0892,0.4209 -0.0523,0.62754 0.0507,0.28405 0.16934,0.57333 0.36606,0.78442 0.24471,0.26259 0.59385,0.43291 0.94131,0.52295 0.23624,0.0612 0.48862,0.0162 0.73213,0 0.52642,-0.0349 1.04887,-0.11991 1.56884,-0.20918 0.33358,-0.0573 0.67037,-0.10879 0.9936,-0.20918 0.21641,-0.0672 0.44866,-0.12234 0.62754,-0.26147 0.1376,-0.10702 0.25865,-0.25299 0.31377,-0.41836 0.0331,-0.0992 0,-0.31377 0,-0.31377"/><path d="m 130.59382,494.48101 c 0,0 -0.38846,0.64967 -0.62754,0.9413 -0.34384,0.41942 -0.79514,0.74077 -1.15049,1.15049 -0.22843,0.26338 -0.48186,0.51998 -0.62754,0.83672 -0.13431,0.29201 -0.14424,0.62651 -0.20918,0.9413 -0.0753,0.36496 -0.2284,0.72605 -0.20917,1.0982 0.0188,0.36349 0.19605,0.70147 0.31376,1.04589 0.0785,0.22975 0.12591,0.47841 0.26148,0.67983 0.21347,0.31716 0.51357,0.58014 0.83672,0.78443 0.44325,0.28021 0.94531,0.49977 1.46425,0.57524 0.60597,0.0881 1.22632,-0.0562 1.83032,-0.15688 0.42536,-0.0709 0.84427,-0.18263 1.25508,-0.31377 0.41014,-0.13092 0.83216,-0.25158 1.20278,-0.47066 0.2344,-0.13856 0.44554,-0.32042 0.62753,-0.52295 0.25205,-0.2805 0.51826,-0.58038 0.62754,-0.9413 0.0758,-0.25025 -0.0153,-0.52339 0,-0.78442 0.0175,-0.29787 0.046,-0.59645 0.10459,-0.88902 0.0498,-0.24886 0.20918,-0.73212 0.20918,-0.73212"/><path d="m 136.29395,499.5536 c 0,0 0.5456,-0.20412 0.78442,-0.36606 0.33682,-0.22839 0.66213,-0.4989 0.88902,-0.83672 0.27074,-0.40311 0.40287,-0.88915 0.52294,-1.35966 0.13045,-0.5112 0.17424,-1.04243 0.20918,-1.56885 0.0393,-0.59137 0.10056,-1.19394 0,-1.77802 -0.0973,-0.56508 -0.36277,-1.08857 -0.57524,-1.62114 -0.19085,-0.47838 -0.34284,-0.98276 -0.62754,-1.41196 -0.21133,-0.31859 -0.49271,-0.58961 -0.78442,-0.83672 -0.19183,-0.1625 -0.62754,-0.41836 -0.62754,-0.41836"/><path d="m 137.13067,490.08824 c 0,0 0.1307,-1.07887 0.15688,-1.62114 0.016,-0.33081 -0.0505,-0.66627 0,-0.9936 0.0529,-0.34327 0.23666,-0.65495 0.31377,-0.9936 0.13683,-0.60092 0.17968,-1.21947 0.26148,-1.83032 0.0746,-0.55718 0.15869,-1.11355 0.20918,-1.67343 0.0282,-0.31298 -0.0131,-0.63394 0.0523,-0.94131 0.0816,-0.38314 0.36032,-0.71079 0.41836,-1.09819 0.0388,-0.25916 -0.0436,-0.52251 -0.0523,-0.78442 -0.01,-0.29618 -0.021,-0.59343 0,-0.88902 0.0349,-0.4918 0.17423,-0.97245 0.20918,-1.46425 0.0173,-0.24343 -0.0186,-0.4888 0,-0.73213 0.0524,-0.68583 0.17636,-1.36553 0.31377,-2.0395 0.18327,-0.89895 0.50752,-1.76592 0.67984,-2.66703 0.10234,-0.53516 0.25465,-1.07818 0.20917,-1.62114 -0.035,-0.41762 -0.25419,-0.7989 -0.36606,-1.20278 -0.13429,-0.48485 -0.20117,-0.98894 -0.36606,-1.46426 -0.2506,-0.72238 -0.64237,-1.38804 -0.94131,-2.09179 -0.1468,-0.3456 -0.41836,-1.0459 -0.41836,-1.0459"/><path d="m 138.49033,470.94834 c 0,0 -0.29329,-1.45774 -0.36606,-2.19639 -0.0547,-0.55539 -0.0436,-1.11542 -0.0523,-1.67343 -0.008,-0.54031 0.0612,-1.08423 0,-1.62114 -0.0526,-0.46215 -0.21585,-0.90496 -0.31377,-1.35967 -0.13098,-0.60824 -0.2539,-1.21832 -0.36607,-1.83031 -0.1147,-0.62577 -0.2613,-1.24859 -0.31377,-1.88262 -0.0417,-0.50379 0.0401,-1.01262 0,-1.51655 -0.0699,-0.87989 -0.36754,-1.73354 -0.41835,-2.61474 -0.0462,-0.80128 0.0491,-1.60487 0.10459,-2.40556 0.0763,-1.10052 0.11428,-2.2096 0.31376,-3.29457 0.22559,-1.22699 0.65544,-2.40751 0.99361,-3.60835 0.32452,-1.15239 0.69478,-2.29214 0.9936,-3.45146 0.25437,-0.98686 0.48592,-1.98031 0.67983,-2.9808 0.16795,-0.86654 0.26205,-1.74602 0.41836,-2.61474 0.22036,-1.22471 0.42098,-2.45579 0.73213,-3.66064 0.30188,-1.16897 0.6859,-2.31672 1.09819,-3.45146 0.39243,-1.08008 0.90585,-2.11324 1.30737,-3.18998 0.61055,-1.63729 1.19303,-3.28792 1.67343,-4.96801 0.27084,-0.9472 0.55579,-1.8989 0.67984,-2.87622 0.10758,-0.84752 0.0797,-1.70855 0.0523,-2.56244 -0.0331,-1.03162 -0.16242,-2.05801 -0.26147,-3.0854 -0.12451,-1.29146 -0.33193,-2.57524 -0.41836,-3.86981 -0.0906,-1.35709 -0.0484,-2.72005 -0.10459,-4.079 -0.0253,-0.61058 -0.0952,-1.21929 -0.10459,-1.83032 -0.0102,-0.66255 0.0335,-1.32484 0.0523,-1.9872 0.0163,-0.57528 -0.0485,-1.15912 0.0523,-1.72573 0.0676,-0.3799 0.21069,-0.74499 0.36606,-1.09819 0.36133,-0.82139 0.85153,-1.58033 1.30737,-2.35327 0.58477,-0.99156 1.25462,-1.93166 1.83032,-2.92851 0.46409,-0.80359 0.90078,-1.6237 1.30737,-2.45786 0.52655,-1.08027 0.98781,-2.19128 1.46426,-3.29457 0.46462,-1.07591 0.97367,-2.13573 1.35966,-3.24228 0.38169,-1.09425 0.72914,-2.20755 0.94131,-3.34687 0.16989,-0.91229 0.21784,-1.84467 0.26147,-2.77162 0.0606,-1.28851 0.0692,-2.58174 0,-3.86982 -0.0611,-1.13797 -0.30496,-2.26119 -0.36606,-3.39916 -0.0579,-1.07921 0,-2.16152 0,-3.24228 0,-1.11562 0.005,-2.23126 0,-3.34687 -0.009,-1.86524 -0.0761,-3.73044 -0.0523,-5.59555 0.0191,-1.49991 0.088,-2.99891 0.15689,-4.49735 0.0281,-0.61046 0.0446,-1.22217 0.10459,-1.83032 0.0984,-0.9985 0.26065,-1.98994 0.41836,-2.98081 0.20316,-1.27646 0.47392,-2.5415 0.67983,-3.81752 0.21325,-1.32151 0.33034,-2.65839 0.57524,-3.9744 0.18645,-1.00192 0.49866,-1.97793 0.67984,-2.98081 0.30329,-1.67881 0.35914,-3.39703 0.67983,-5.0726 0.2567,-1.34123 0.69714,-2.6414 0.9936,-3.9744 0.31617,-1.42162 0.613,-2.84912 0.83672,-4.28818 0.23185,-1.4913 0.37311,-2.99559 0.52295,-4.49735 0.16672,-1.67094 0.34856,-3.34252 0.41835,-5.02031 0.0732,-1.75907 0.0137,-3.52123 0,-5.28177 -0.009,-1.11573 -0.003,-2.23219 -0.0523,-3.34687 -0.15145,-3.43858 -0.74701,-10.29867 -0.74701,-10.29867"/><path d="m 189.6949,470.84577 c 0,0 -0.0434,-1.28337 0,-1.92285 0.0371,-0.54611 0.18476,-1.08093 0.22186,-1.62704 0.0417,-0.61489 -0.0715,-1.23676 0,-1.8489 0.0931,-0.79713 0.42797,-1.55039 0.55464,-2.34287 0.16287,-1.01921 0.15182,-2.05908 0.26147,-3.08539 0.11576,-1.08355 0.35806,-2.15423 0.41836,-3.24228 0.055,-0.99223 0.0349,-1.99088 -0.0523,-2.98081 -0.10682,-1.21328 -0.3599,-2.40956 -0.57525,-3.60834 -0.15715,-0.87484 -0.31274,-1.75111 -0.52294,-2.61474 -0.31314,-1.28655 -0.76399,-2.53628 -1.0982,-3.81752 -0.28922,-1.10875 -0.56302,-2.22261 -0.78442,-3.34687 -0.25582,-1.29905 -0.34836,-2.62788 -0.62754,-3.92211 -0.29336,-1.35998 -0.6727,-2.70211 -1.09819,-4.0267 -0.55159,-1.71714 -1.25436,-3.382 -1.88261,-5.0726 -0.27859,-0.74968 -0.57908,-1.49155 -0.83672,-2.24868 -0.32327,-0.94999 -0.64066,-1.90394 -0.88901,-2.87621 -0.28174,-1.10299 -0.53223,-2.21807 -0.67983,-3.34687 -0.0731,-0.5587 -0.11976,-1.12422 -0.10076,-1.68735 0.0393,-1.16739 0.32297,-2.31415 0.44373,-3.47594 0.11251,-1.08235 0.19727,-2.16777 0.26147,-3.25406 0.0947,-1.60074 0.15187,-3.2039 0.18227,-4.80714 0.0206,-1.0845 0.0451,-2.17032 0,-3.25407 -0.0247,-0.59319 -0.009,-1.19767 -0.14791,-1.77495 -0.13686,-0.56977 -0.41845,-1.09573 -0.66561,-1.62703 -0.2465,-0.52988 -0.53464,-1.0395 -0.81351,-1.55308 -0.64785,-1.19311 -1.35945,-2.35115 -1.99682,-3.54989 -0.6524,-1.227 -1.29927,-2.45903 -1.8694,-3.72635 -0.53917,-1.19851 -0.99059,-2.43475 -1.46425,-3.66064 -0.3956,-1.02387 -0.84352,-2.03155 -1.15049,-3.08539 -0.30405,-1.04383 -0.57249,-2.10809 -0.67983,-3.18999 -0.14113,-1.42251 0.0104,-2.85929 0.0523,-4.28817 0.066,-2.25014 0.27327,-4.49529 0.31377,-6.74603 0.0298,-1.65583 -0.0361,-3.31199 -0.0523,-4.96801 -0.0188,-1.91746 -0.0695,-3.83495 -0.0523,-5.75243 0.006,-0.64518 0.0772,-1.29018 0.0523,-1.93491 -0.0452,-1.17341 -0.222,-2.33835 -0.36607,-3.50376 -0.0907,-0.73397 -0.21936,-1.46287 -0.31376,-2.19638 -0.215,-1.67061 -0.33619,-3.35297 -0.57525,-5.0203 -0.21842,-1.52335 -0.53599,-3.03091 -0.78442,-4.54965 -0.23919,-1.46225 -0.39589,-2.93854 -0.67983,-4.39277 -0.37757,-1.9338 -0.94325,-3.82662 -1.35967,-5.75243 -0.40172,-1.85783 -0.81612,-3.71582 -1.09819,-5.59554 -0.17426,-1.16127 -0.25248,-2.33499 -0.36606,-3.50376 -0.15066,-1.55036 -0.34176,-3.09845 -0.41836,-4.65423 -0.0978,-1.98487 -0.0583,-3.97434 -0.0523,-5.96161 0.004,-1.15061 -0.01,-2.30251 0.0523,-3.45146 0.18154,-3.36674 0.93516,-10.07156 0.93516,-10.07156"/><path d="m 130.01235,370.3395 c 0,0 -0.0389,1.87436 0,2.81033 0.0494,1.18637 0.24648,2.36352 0.29583,3.54989 0.0389,0.93597 0.097,1.87859 0,2.81033 -0.0991,0.95216 -0.29176,1.9012 -0.59165,2.81033 -0.40777,1.23615 -1.34948,2.27816 -1.62703,3.54989 -0.25232,1.15608 -0.17183,2.37914 0,3.54989 0.1495,1.01859 0.88747,2.95825 0.88747,2.95825"/><path d="m 143.47235,392.23049 c 0,0 1.20152,-3.02029 1.62704,-4.58527 0.3425,-1.25966 0.63816,-2.54426 0.73956,-3.84571 0.11114,-1.42635 0.17639,-2.89603 -0.14791,-4.28946 -0.24511,-1.05318 -0.80765,-2.01212 -1.33121,-2.95824 -0.51643,-0.93325 -1.77495,-2.66242 -1.77495,-2.66242"/><path d="m 148.35345,377.5872 c 0,0 1.50614,-3.63778 2.21869,-5.47275 0.66635,-1.71599 1.45357,-3.39691 1.92285,-5.17692 0.39468,-1.49703 0.73956,-4.58528 0.73956,-4.58528"/><path d="m 174.97763,366.78961 c 0,0 1.15747,3.84512 2.07077,5.62066 0.68181,1.32551 1.63932,2.49121 2.51451,3.69781 0.80486,1.10963 2.5145,3.25406 2.5145,3.25406"/><path d="m 198.34774,370.19159 c 0,0 -0.24291,2.37442 -0.44373,3.54989 -0.19543,1.14391 -0.75203,2.24157 -0.73956,3.40198 0.0136,1.26753 0.50771,2.48842 0.88747,3.6978 0.36482,1.16179 1.04408,2.2186 1.33121,3.40198 0.33894,1.39692 0.40088,2.85264 0.44373,4.28945 0.0338,1.13456 0.13681,2.30321 -0.14791,3.40198 -0.22124,0.85378 -1.1833,2.36659 -1.1833,2.36659"/><path d="m 182.96488,377.14346 c 0,0 -0.61487,1.54956 -0.73956,2.36659 -0.17852,1.16975 -0.15375,2.37662 0,3.54989 0.1989,1.51783 0.56121,3.03866 1.1833,4.43737 0.47794,1.07459 1.19736,2.03259 1.92286,2.95824 0.66704,0.85107 2.21868,2.36659 2.21868,2.36659"/><path d="m 144.80356,400.06984 c 0,0 -2.86877,2.35423 -4.14153,3.6978 -1.30268,1.37515 -3.5499,4.43736 -3.5499,4.43736"/><path d="m 182.66906,400.36566 c 0,0 2.40516,3.72329 3.54989,5.62066 0.96986,1.60753 2.81033,4.8811 2.81033,4.8811"/><path d="m 153.67829,287.80455 c 0,0 -3.95325,-5.68738 -6.0644,-8.43098 -1.75166,-2.27642 -3.61877,-4.46215 -5.47274,-6.65605 -1.60164,-1.89531 -4.8811,-5.62066 -4.8811,-5.62066"/><path d="m 194.50203,265.02609 c 0,0 -3.63995,2.85642 -5.32484,4.43736 -1.88205,1.76593 -3.55133,3.74574 -5.32483,5.62066 -1.67771,1.77365 -3.49278,3.42733 -5.02901,5.32484 -1.58343,1.95581 -4.28945,6.21231 -4.28945,6.21231"/><path d="m 189.87978,465.22511 c 0,0 -0.49028,0.86711 -0.66561,1.33121 -0.15321,0.40555 -0.20873,0.84187 -0.3328,1.25726 -0.13387,0.44817 -0.31146,0.88256 -0.44374,1.3312 -0.12598,0.42726 -0.24457,0.85762 -0.3328,1.29424 -0.0666,0.32977 -0.13203,0.66234 -0.14791,0.9984 -0.0111,0.23426 0.005,0.47029 0.037,0.70258 0.0383,0.27544 0.11624,0.54404 0.18489,0.81352 0.14546,0.57097 0.35305,1.12578 0.48071,1.70099 0.11635,0.52424 0.12226,1.07072 0.25885,1.59006 0.0635,0.24137 0.21502,0.45688 0.25884,0.70258 0.0476,0.26696 0.006,0.54242 0,0.81351 -0.006,0.25907 -0.0724,0.51983 -0.037,0.77654 0.032,0.23168 0.17892,0.43572 0.22186,0.66561 0.0476,0.25473 0.0511,0.51778 0.037,0.77654 -0.0129,0.23674 -0.12365,0.46583 -0.11093,0.70258 0.0254,0.47174 0.30761,0.89987 0.36978,1.36818 0.0373,0.28103 -0.0269,0.56828 0,0.8505 0.031,0.32488 0.11447,0.64277 0.18489,0.96143 0.0768,0.34737 0.21537,0.6823 0.25884,1.03538 0.0437,0.35478 -0.0596,0.71991 0,1.07237 0.05,0.29596 0.23716,0.55612 0.29583,0.85049 0.0821,0.41171 0.0493,0.83817 0.0739,1.25725 0.0247,0.41909 0.0408,0.83877 0.074,1.25726 0.0196,0.24697 0.11098,0.81352 0.11098,0.81352"/><path d="m 192.13544,488.74314 c 0,0 -0.5734,0.53581 -0.8505,0.81351 -0.25249,0.25303 -0.5341,0.48403 -0.73956,0.77654 -0.20594,0.2932 -0.32951,0.63659 -0.48071,0.96143 -0.24929,0.53557 -0.54341,1.05813 -0.70259,1.62703 -0.12071,0.43143 -0.16715,0.88357 -0.18489,1.33121 -0.0166,0.41948 0.0432,0.83858 0.074,1.25726 0.0308,0.41958 0.021,0.84627 0.11093,1.25725 0.11756,0.537 0.26589,1.08533 0.55467,1.55308 0.20609,0.33381 0.48842,0.6309 0.81352,0.85049 0.22002,0.14861 0.73956,0.29582 0.73956,0.29582"/><path d="m 191.28494,497.83973 c 0,0 0.20395,0.45911 0.25885,0.70258 0.0599,0.26562 0.0164,0.54736 0.0739,0.81352 0.0634,0.29339 0.16098,0.58233 0.29583,0.85049 0.16742,0.33292 0.35138,0.67546 0.62862,0.92446 0.31179,0.28003 0.71933,0.43828 1.10934,0.59164 0.58153,0.22867 1.19739,0.36756 1.81193,0.48072 0.46319,0.0853 0.93429,0.13792 1.40516,0.14791 0.39511,0.008 0.80169,0.0288 1.1833,-0.074 0.42582,-0.11467 0.87381,-0.2775 1.1833,-0.59164 0.25923,-0.26313 0.35731,-0.65026 0.48071,-0.99841 0.16081,-0.45369 0.30348,-0.92472 0.3328,-1.40517 0.0204,-0.33423 -0.037,-0.67182 -0.11093,-0.9984 -0.0663,-0.29275 -0.15573,-0.58504 -0.29583,-0.8505 -0.16455,-0.31177 -0.41151,-0.57275 -0.62862,-0.85049 -0.22646,-0.28971 -0.44268,-0.59037 -0.70258,-0.8505 -0.32794,-0.32824 -0.77776,-0.52901 -1.07237,-0.88747 -0.21362,-0.25991 -0.48071,-0.88747 -0.48071,-0.88747"/><path d="m 199.605,501.05682 c 0,0 0.40459,0.45026 0.6656,0.59165 0.37072,0.20082 0.80411,0.26526 1.22028,0.3328 0.43868,0.0712 0.88714,0.0561 1.3312,0.074 0.4928,0.0199 1.01843,0.21307 1.47913,0.037 0.26879,-0.10272 0.49604,-0.33625 0.62862,-0.59164 0.0803,-0.15472 0.0616,-0.34382 0.074,-0.5177 0.021,-0.29508 0.068,-0.59956 0,-0.88747 -0.057,-0.24142 -0.25756,-0.42923 -0.3328,-0.6656 -0.0492,-0.15449 -0.0493,-0.32048 -0.074,-0.48072 -0.0247,-0.16024 -0.033,-0.32386 -0.074,-0.48071 -0.0533,-0.20378 -0.1315,-0.40139 -0.22186,-0.59165 -0.0735,-0.15468 -0.18689,-0.28835 -0.25885,-0.44374 -0.0934,-0.20164 -0.14256,-0.42105 -0.22187,-0.62862 -0.0809,-0.21169 -0.13727,-0.43739 -0.25885,-0.62863 -0.10765,-0.16933 -0.32178,-0.26197 -0.40675,-0.44374 -0.079,-0.16898 -0.074,-0.55467 -0.074,-0.55467"/><path d="m 204.92983,501.68545 c 0,0 0.66632,-0.0119 0.99841,-0.037 0.43298,-0.0327 0.8885,0.007 1.29423,-0.14791 0.23966,-0.0914 0.44676,-0.26288 0.62863,-0.44374 0.15037,-0.14953 0.30506,-0.31574 0.36978,-0.51769 0.0677,-0.21129 0.039,-0.44719 0,-0.66561 -0.0438,-0.2457 -0.12434,-0.49235 -0.25885,-0.70258 -0.0658,-0.10278 -0.19044,-0.15781 -0.25885,-0.25885 -0.10525,-0.15546 -0.17499,-0.33589 -0.22186,-0.51769 -0.0309,-0.11995 -0.007,-0.24967 -0.037,-0.36978 -0.0392,-0.15536 -0.11506,-0.29951 -0.18489,-0.44373 -0.0553,-0.11422 -0.15306,-0.20996 -0.18489,-0.33281 -0.0371,-0.14318 0.0181,-0.29693 0,-0.44373 -0.0186,-0.15132 -0.0526,-0.30288 -0.11094,-0.44374 -0.055,-0.1328 -0.14868,-0.24607 -0.22187,-0.36978 -0.0872,-0.14738 -0.20396,-0.28153 -0.25884,-0.44374 -0.0319,-0.0941 -0.037,-0.29582 -0.037,-0.29582"/><path d="m 207.96203,500.94589 c 0,0 0.51769,0.11093 0.6656,0.11093 0.14792,0 0.47488,-0.0743 0.70259,-0.14791 0.23101,-0.0747 0.47479,-0.14569 0.6656,-0.29583 0.15888,-0.12501 0.30468,-0.28932 0.36978,-0.48071 0.0794,-0.23339 -0.0128,-0.49337 0,-0.73956 0.0309,-0.59405 0.18885,-1.18011 0.18489,-1.77495 -0.003,-0.42196 -0.10642,-0.83732 -0.14791,-1.25725 -0.0304,-0.30764 0.0399,-0.63706 -0.074,-0.92445 -0.0582,-0.14675 -0.18611,-0.25629 -0.29582,-0.36978 -0.079,-0.0817 -0.25885,-0.22187 -0.25885,-0.22187"/><path d="m 210.43956,500.05841 c 0,0 0.64066,0.0944 0.96143,0.074 0.36429,-0.0232 0.73853,-0.0742 1.07236,-0.22187 0.30665,-0.13562 0.59679,-0.33581 0.81352,-0.59165 0.21378,-0.25236 0.3593,-0.56769 0.44373,-0.88747 0.0599,-0.22675 0.0308,-0.46814 0.037,-0.70258 0.005,-0.19715 -0.0262,-0.39618 0,-0.59165 0.0373,-0.27859 0.16419,-0.53842 0.22187,-0.81352 0.069,-0.32927 0.16795,-0.66256 0.14791,-0.9984 -0.0167,-0.28058 -0.14355,-0.54357 -0.22187,-0.81352 -0.0934,-0.32202 -0.17641,-0.64811 -0.29582,-0.96143 -0.11589,-0.30408 -0.2419,-0.60691 -0.40676,-0.88747 -0.11616,-0.19768 -0.25983,-0.37866 -0.40676,-0.55467 -0.20673,-0.24766 -0.41999,-0.49342 -0.6656,-0.70258 -0.24988,-0.2128 -0.56079,-0.34528 -0.81352,-0.55468 -0.26846,-0.22243 -0.50705,-0.47978 -0.73956,-0.73956 -0.21055,-0.23524 -0.36906,-0.51568 -0.59165,-0.73956 -0.23481,-0.23617 -0.5332,-0.40126 -0.77654,-0.62862 -0.17207,-0.16077 -0.32789,-0.33853 -0.48071,-0.51769 -0.23362,-0.2739 -0.47589,-0.54455 -0.66561,-0.8505 -0.16561,-0.26707 -0.28192,-0.5621 -0.40675,-0.85049 -0.18913,-0.43694 -0.28644,-0.91504 -0.5177,-1.33121 -0.17961,-0.32323 -0.47338,-0.57158 -0.6656,-0.88748 -0.20633,-0.33909 -0.33211,-0.72149 -0.51769,-1.07236 -0.17299,-0.32706 -0.37238,-0.63947 -0.55467,-0.96143 -0.18758,-0.33129 -0.36663,-0.66737 -0.55467,-0.9984 -0.21824,-0.38419 -0.66561,-1.14632 -0.66561,-1.14632"/><path d="m 206.03917,483.34435 c 0,0 -0.11111,-0.54037 -0.14791,-0.81352 -0.0562,-0.41694 -0.0396,-0.84262 -0.11093,-1.25725 -0.0669,-0.38892 -0.12974,-0.78835 -0.29583,-1.14632 -0.15258,-0.32884 -0.41908,-0.59165 -0.62862,-0.88747 -0.20954,-0.29583 -0.41666,-0.59339 -0.62863,-0.88748 -0.26812,-0.372 -0.5974,-0.70491 -0.81352,-1.10934 -0.13599,-0.25449 -0.29582,-0.81351 -0.29582,-0.81351"/><path d="m 204.33818,478.42627 c 0,0 -0.0687,-0.46715 -0.0739,-0.70258 -0.009,-0.40741 0.0135,-0.81727 0.0739,-1.22028 0.0545,-0.36366 0.1412,-0.72397 0.25885,-1.07236 0.10772,-0.31896 0.3252,-0.59782 0.40676,-0.92445 0.11977,-0.4797 0.11706,-0.98473 0.11093,-1.47912 -0.006,-0.49546 -0.063,-0.99096 -0.14791,-1.47912 -0.0697,-0.40055 -0.13594,-0.80948 -0.29582,-1.1833 -0.10892,-0.25468 -0.32783,-0.45101 -0.44374,-0.70258 -0.22677,-0.4922 -0.34369,-1.02876 -0.48072,-1.55308 -0.0892,-0.34149 -0.16064,-0.68777 -0.22186,-1.03538 -0.1403,-0.79658 -0.25968,-1.59806 -0.33281,-2.40358 -0.0513,-0.56521 -0.074,-1.55307 -0.074,-1.70099 0,-0.14791 0.0595,-1.50462 0.11093,-2.25566 0.0481,-0.70363 0.11099,-1.40634 0.18489,-2.10774 0.0846,-0.80279 0.18132,-1.6045 0.29583,-2.40357 0.0974,-0.68 0.19594,-1.36062 0.3328,-2.0338 0.19714,-0.9697 0.66559,-2.73637 0.70258,-2.88428 0.037,-0.14791 0.46111,-1.67193 0.66561,-2.51451 0.25605,-1.05497 0.51166,-2.11143 0.70258,-3.18011 0.15972,-0.89404 0.22205,-1.80329 0.36978,-2.69939 0.11639,-0.70602 0.28599,-1.40247 0.40676,-2.10775 0.30923,-1.80582 0.5742,-3.61936 0.81351,-5.43577 0.12802,-0.97166 0.22963,-1.94665 0.33281,-2.92126 0.11996,-1.13307 0.22268,-2.26791 0.3328,-3.40198 0.0993,-1.02299 0.13403,-2.05419 0.29582,-3.06918 0.15111,-0.94796 0.48366,-1.86141 0.62863,-2.81033 0.13449,-0.88034 0.14509,-1.77519 0.22187,-2.66242 0.0832,-0.9617 0.24136,-1.91915 0.25884,-2.88428 0.0168,-0.92561 -0.10546,-1.84856 -0.14791,-2.77335 -0.0294,-0.64075 -0.0528,-1.28178 -0.074,-1.92286 -0.0294,-0.88733 -0.008,-1.77704 -0.074,-2.66242 -0.0836,-1.12674 -0.23784,-2.24787 -0.40676,-3.365 -0.12363,-0.81756 -0.2887,-1.62836 -0.44374,-2.44055 -0.1532,-0.80256 -0.31196,-1.60413 -0.48071,-2.40357 -0.14082,-0.66714 -0.27897,-1.33518 -0.44374,-1.99681 -0.32447,-1.30289 -0.71945,-2.58722 -1.07236,-3.8827 -0.22476,-0.82506 -0.48018,-1.64274 -0.6656,-2.47752 -0.18455,-0.83087 -0.22409,-1.69222 -0.44374,-2.51451 -0.19622,-0.73457 -0.56906,-1.41325 -0.77654,-2.14472 -0.16492,-0.58142 -0.21233,-1.19147 -0.36978,-1.77495 -0.0812,-0.30106 -0.23566,-0.5815 -0.29582,-0.88747 -0.10726,-0.54546 -0.0869,-1.10863 -0.11094,-1.66401 -0.0267,-0.61585 -0.0368,-1.23248 -0.037,-1.8489 -2.5e-4,-0.64107 0.0173,-1.28209 0.037,-1.92286 0.0269,-0.87551 0.037,-2.47752 0.11094,-2.62544 0.0739,-0.1479 -0.0214,-1.10942 -0.037,-1.66401 -0.0204,-0.72737 -0.0375,-1.45497 -0.074,-2.18171 -0.0651,-1.29547 -0.20094,-2.58688 -0.25884,-3.88269 -0.0484,-1.08389 -0.0205,-2.17041 -0.074,-3.25406 -0.0561,-1.13589 -0.20495,-2.26599 -0.25885,-3.40198 -0.031,-0.65266 -0.0308,-1.30647 -0.037,-1.95984 -0.006,-0.6286 -0.0725,-1.26144 0,-1.88588 0.0744,-0.64149 0.30933,-1.25423 0.44373,-1.88588 0.16452,-0.77319 0.30671,-1.55108 0.44374,-2.32961 0.21428,-1.2174 0.40801,-2.43844 0.59165,-3.66083 0.19967,-1.32907 0.39533,-2.65911 0.55467,-3.99362 0.17624,-1.47602 0.27564,-2.9604 0.44373,-4.43737 0.19812,-1.74083 0.47764,-3.47194 0.66561,-5.2139 0.18054,-1.67314 0.44373,-4.8811 0.44373,-5.02901 0,-0.14791 0.0793,-2.41574 0.11094,-3.62384 0.0297,-1.13387 0.0453,-2.26808 0.074,-3.40198 0.0433,-1.71348 0.0974,-3.42667 0.14791,-5.13995 0.0723,-2.45293 0.19968,-4.90474 0.22187,-7.35863 0.0185,-2.04618 -0.0162,-4.0929 -0.074,-6.13835 -0.0313,-1.10999 -0.0837,-2.21944 -0.14791,-3.32802 -0.14007,-2.418 -0.24858,-4.84064 -0.5177,-7.24769 -0.16348,-1.46218 -0.44958,-2.90806 -0.6656,-4.36341 -0.17737,-1.19492 -0.33435,-2.39285 -0.51769,-3.58687 -0.0815,-0.53077 -0.21909,-1.05453 -0.25885,-1.59005 -0.0694,-0.93429 0.0238,-1.87356 0.037,-2.81033 0.0116,-0.82585 0.0576,-1.65185 0.037,-2.47753 -0.0569,-2.28439 -0.20593,-4.56824 -0.44374,-6.84093 -0.0985,-0.9414 -0.25854,-1.87547 -0.40676,-2.81033 -0.1136,-0.71651 -0.22531,-1.4338 -0.36978,-2.14473 -0.48405,-2.38204 -1.14825,-4.7244 -1.66401,-7.09978 -0.28005,-1.28981 -0.52341,-2.58733 -0.77654,-3.88269 -0.31527,-1.61333 -0.58204,-3.23633 -0.92445,-4.84412 -0.17935,-0.84217 -0.43716,-1.66742 -0.59165,-2.51451 -0.0513,-0.28126 -0.11093,-0.70258 -0.11093,-0.85049 0,-0.14792 0.0264,-1.10931 0.037,-1.66402 0.0147,-0.76417 0.0689,-1.52899 0.037,-2.29263 -0.031,-0.7426 -0.14717,-1.4792 -0.22187,-2.21868 -0.12204,-1.20807 -0.2261,-2.41816 -0.36978,-3.62385 -0.16192,-1.35879 -0.32944,-2.71783 -0.55467,-4.06758 -0.17785,-1.06581 -0.59164,-2.99522 -0.62863,-3.18011 -0.037,-0.18489 -0.36974,-2.69093 -0.59165,-4.03061 -0.13314,-0.80378 -0.33068,-1.59672 -0.44373,-2.40357 -0.0894,-0.63768 -0.14399,-1.28025 -0.18489,-1.92286 -0.0501,-0.78766 -0.10304,-1.57788 -0.074,-2.36659 0.0347,-0.94131 0.18809,-1.87456 0.29582,-2.81033 0.10229,-0.88851 0.25523,-1.77141 0.33281,-2.66242 0.0867,-0.99586 0.0916,-1.99718 0.14791,-2.99522 0.0438,-0.77686 0.0821,-1.5543 0.14791,-2.32961 0.0986,-1.16101 0.30806,-2.31239 0.36978,-3.47594 0.0464,-0.87392 -0.0109,-1.75036 0,-2.62544 0.0123,-0.98631 0.0722,-1.97185 0.074,-2.95824 10e-4,-0.57945 -0.075,-1.15976 -0.037,-1.73797 0.0213,-0.32355 0.0306,-0.65916 0.14791,-0.96143 0.0322,-0.0829 0.12215,-0.13679 0.14791,-0.22186 0.12862,-0.42469 0.0128,-0.88765 2.1e-4,-1.33121 -0.0492,-1.72776 -0.2181,-3.45022 -0.29582,-5.17693 -0.0843,-1.87267 -0.13262,-3.74682 -0.18489,-5.62066 -0.045,-1.6145 -0.18431,-3.23066 -0.11093,-4.84412 0.0197,-0.43377 0.0659,-0.86783 0.14791,-1.29423 0.10618,-0.55203 0.21085,-1.11538 0.44373,-1.62703 0.23934,-0.52584 0.642,-0.96073 0.96143,-1.44214 0.43284,-0.65234 0.96086,-1.25149 1.29423,-1.95984 0.32377,-0.68795 0.66561,-2.1817 0.66561,-2.1817"/><path d="m 198.7545,200.75828 c 0,0 0.082,1.35728 0.14791,2.0338 0.10836,1.11233 0.2322,2.22414 0.40676,3.32802 0.21182,1.33949 0.50973,2.66399 0.77654,3.99362 0.21545,1.07367 0.46003,2.14148 0.6656,3.21709 0.26781,1.40126 0.47315,2.81397 0.73957,4.2155 0.19502,1.02592 0.4135,2.04727 0.62862,3.06917 0.19224,0.91319 0.49248,1.80846 0.59165,2.73638 0.0707,0.66183 0.0233,1.33162 0,1.99681 -0.0247,0.70388 -0.0795,1.40676 -0.14791,2.10775 -0.0579,0.59344 -0.21182,1.17877 -0.22187,1.77494 -0.009,0.54451 0.0364,1.09399 0.14791,1.62704 0.0718,0.34337 0.27661,0.65213 0.3328,0.9984 0.0415,0.2555 -0.003,0.51771 0,0.77654 0.006,0.53013 -0.0129,1.06225 0.037,1.59006 0.0353,0.37322 0.0884,0.7471 0.18489,1.10934 0.11849,0.44469 0.33079,0.85913 0.48072,1.29423 0.0927,0.26904 0.19453,0.53631 0.25884,0.81351 0.13236,0.57056 0.18503,1.15693 0.25885,1.73797 0.0594,0.46722 0.0239,0.95081 0.14791,1.40517 0.2033,0.74498 0.62191,1.41416 0.96143,2.10774 0.38542,0.78735 0.83168,1.54383 1.22027,2.32962 0.53045,1.07265 1.03548,2.15819 1.5161,3.25407 0.54609,1.24518 1.01062,2.52498 1.55308,3.77175 0.4599,1.05702 0.9663,2.0932 1.44214,3.14314 0.58533,1.29152 1.22196,2.56194 1.73797,3.88269 0.61986,1.58657 1.08018,3.23093 1.62703,4.84412 0.47679,1.4065 1.02132,2.79124 1.44215,4.21549 0.15841,0.53612 0.23142,1.09621 0.40675,1.62704 0.17158,0.51948 0.40813,1.01542 0.62863,1.5161 0.2467,0.56018 0.51022,1.11289 0.77654,1.66401 0.13191,0.27298 0.28192,0.53723 0.40676,0.81351 0.20264,0.44846 0.35681,0.9176 0.55467,1.36819 0.20838,0.47454 0.4169,0.95046 0.6656,1.40517 0.22319,0.40808 0.52036,0.77305 0.73956,1.18329 0.1274,0.23843 0.27608,0.47525 0.33281,0.73956 0.0595,0.27719 0.003,0.56701 0,0.8505 -0.006,0.60407 -0.0553,1.2081 -0.037,1.81192 0.0277,0.9147 0.12812,1.82608 0.22187,2.73638 0.10181,0.98852 0.17423,1.98392 0.36978,2.95824 0.15359,0.76528 0.35327,1.5253 0.62862,2.25566 0.27032,0.71703 0.67592,1.37563 0.99841,2.07077 0.42029,0.90596 0.81025,1.82571 1.22027,2.73637 0.24458,0.54322 0.51289,1.07609 0.73956,1.62703 0.22999,0.55902 0.37402,1.15275 0.62863,1.70099 0.17902,0.38548 0.47513,0.713 0.62863,1.10934 0.10043,0.25932 0.0912,0.55168 0.18489,0.81352 0.11141,0.31141 0.36157,0.5671 0.44373,0.88747 0.0797,0.31066 0.0145,0.64151 0.037,0.96143 0.034,0.48204 0.12323,0.95954 0.14791,1.44214 0.034,0.66474 -0.0289,1.33184 0,1.99682 0.0123,0.2843 0.0639,0.5661 0.074,0.85049 0.0281,0.78846 -0.0308,1.57765 -0.037,2.36659 -0.005,0.61628 -0.0187,1.23289 0,1.84891 0.0123,0.40732 -0.0129,0.82214 0.074,1.22027 0.0874,0.40031 0.31336,0.75788 0.44373,1.14632 0.11421,0.34028 0.1697,0.69933 0.29583,1.03538 0.0814,0.21682 0.15681,0.44341 0.29582,0.62863 0.16774,0.22351 0.37911,0.42885 0.62863,0.55467 0.15758,0.0795 0.34126,0.10688 0.51769,0.11093 0.22487,0.005 0.47566,0.01 0.66561,-0.11093 0.16458,-0.10438 0.22889,-0.31583 0.3328,-0.48071 0.10597,-0.16815 0.24481,-0.32561 0.29582,-0.5177 0.0664,-0.25017 0.003,-0.51771 0,-0.77653 -0.0123,-0.91238 -0.0722,-1.82392 -0.0739,-2.73638 -9.9e-4,-0.53016 0.0228,-1.06008 0.037,-1.59005 0.0109,-0.4068 0.0243,-0.81353 0.037,-1.22028 0.012,-0.38212 -0.0473,-0.77343 0.037,-1.14632 0.0475,-0.20997 0.20177,-0.38409 0.25885,-0.59165 0.10541,-0.38327 0.13339,-0.78606 0.14791,-1.18329 0.0176,-0.48102 -0.003,-0.96606 -0.074,-1.44214 -0.03,-0.20106 -0.12307,-0.38989 -0.14791,-0.59165 -0.0151,-0.12234 -0.034,-0.2513 0,-0.36978 0.0321,-0.11178 0.0832,-0.23946 0.18489,-0.29583 0.0539,-0.0299 0.12795,-0.0236 0.18489,0 0.0966,0.04 0.16824,0.13208 0.22187,0.22187 0.066,0.11048 0.0752,0.24615 0.11093,0.36978 0.0639,0.22123 0.13072,0.4418 0.18489,0.66561 0.0859,0.35478 0.1792,0.70984 0.22187,1.07236 0.0476,0.40415 0.0266,0.81346 0.037,1.22027 0.0151,0.59158 -0.008,1.18491 0.037,1.77495 0.0286,0.37196 0.0664,0.7453 0.14791,1.10934 0.0622,0.27769 0.16122,0.54622 0.25885,0.81352 0.13272,0.36337 0.32926,0.70284 0.44373,1.07236 0.19386,0.6258 0.29739,1.27692 0.40676,1.92286 0.0975,0.57583 0.12205,1.16253 0.22187,1.73796 0.10786,0.62175 0.25053,1.23751 0.40676,1.8489 0.15258,0.59712 0.35664,1.18006 0.51769,1.77495 0.11952,0.4415 0.15918,0.90805 0.3328,1.33121 0.11956,0.2914 0.26079,0.58803 0.48072,0.81351 0.16239,0.16648 0.37035,0.29826 0.59164,0.36978 0.17632,0.057 0.3699,0.0511 0.55467,0.037 0.22663,-0.0173 0.44712,-0.0853 0.66561,-0.14791 0.21362,-0.0612 0.44789,-0.0926 0.62862,-0.22187 0.24269,-0.17359 0.46271,-0.41872 0.55468,-0.70258 0.0913,-0.28167 -0.0251,-0.59163 -0.037,-0.88747 -0.0129,-0.32046 0.0204,-0.6459 -0.037,-0.96143 -0.0628,-0.34513 -0.25177,-0.65709 -0.3328,-0.99841 -0.15824,-0.66654 -0.16795,-1.36077 -0.29583,-2.03379 -0.12055,-0.63444 -0.32307,-1.25146 -0.44373,-1.88588 -0.11172,-0.58738 -0.17092,-1.18354 -0.25885,-1.77494 -0.0605,-0.40693 -0.14859,-0.81048 -0.18489,-1.22028 -0.0413,-0.46672 5.9e-4,-0.93812 -0.037,-1.40516 -0.0369,-0.45872 -0.0717,-0.92211 -0.18489,-1.36819 -0.094,-0.37057 -0.29861,-0.70567 -0.40676,-1.07236 -0.0999,-0.33855 -0.12595,-0.69571 -0.22186,-1.03539 -0.0604,-0.21385 -0.19279,-0.40832 -0.22187,-0.62862 -0.021,-0.15933 -0.0766,-0.36708 0.037,-0.48072 0.11364,-0.11364 0.32057,-0.0505 0.48071,-0.037 0.10129,0.009 0.2173,0.009 0.29582,0.074 0.1789,0.14706 0.22328,0.4087 0.29583,0.62863 0.11813,0.35812 0.15083,0.73899 0.22187,1.10934 0.11569,0.60308 0.16468,1.22131 0.3328,1.81192 0.0833,0.2928 0.23462,0.56233 0.3328,0.85049 0.0994,0.29169 0.21527,0.58242 0.25885,0.88748 0.0261,0.18303 -0.0344,0.37301 0,0.55467 0.069,0.36433 0.25197,0.69843 0.40676,1.03538 0.19794,0.4309 0.48041,0.82072 0.6656,1.25725 0.24812,0.58488 0.40366,1.20496 0.59149,1.81189 0.15568,0.50303 0.33326,1.00125 0.44373,1.5161 0.094,0.43803 0.0996,0.8914 0.18489,1.33121 0.1064,0.54882 0.29396,1.07949 0.40676,1.62703 0.10836,0.52595 0.13453,1.06764 0.25885,1.59005 0.0569,0.23892 0.10064,0.489 0.22187,0.70259 0.14653,0.25816 0.34272,0.50389 0.59165,0.6656 0.23863,0.15502 0.52923,0.24614 0.81351,0.25885 0.34058,0.0152 0.70607,-0.0465 0.99841,-0.22187 0.29234,-0.1754 0.49411,-0.48189 0.6656,-0.77654 0.16475,-0.28306 0.28112,-0.60104 0.33281,-0.92445 0.0681,-0.42618 -0.008,-0.86362 -0.037,-1.29423 -0.0392,-0.58127 -0.10113,-1.16143 -0.18489,-1.73797 -0.11714,-0.80626 -0.26862,-1.60788 -0.44374,-2.40357 -0.22426,-1.01896 -0.53148,-2.01804 -0.77654,-3.0322 -0.19595,-0.81092 -0.27366,-1.65504 -0.55467,-2.44055 -0.16711,-0.46712 -0.45488,-0.88207 -0.6656,-1.33121 -0.23442,-0.49967 -0.45373,-1.00647 -0.66561,-1.5161 -0.2847,-0.68478 -0.5687,-1.37072 -0.81351,-2.07076 -0.11069,-0.31651 -0.2598,-0.62807 -0.29583,-0.96143 -0.0159,-0.14757 -0.0254,-0.30909 0.037,-0.44374 0.0734,-0.15813 0.20873,-0.30307 0.36978,-0.36978 0.12527,-0.0519 0.27862,-0.0443 0.40676,0 0.2074,0.0717 0.37689,0.23843 0.51769,0.40676 0.28656,0.34259 0.45147,0.7733 0.62863,1.1833 0.27366,0.63333 0.45551,1.30267 0.6656,1.95983 0.11756,0.36773 0.16571,0.76131 0.3328,1.10934 0.18793,0.39144 0.51866,0.69853 0.73956,1.07236 0.21032,0.35593 0.38782,0.73108 0.55467,1.10934 0.20786,0.47124 0.39339,0.95301 0.55468,1.44215 0.18823,0.57084 0.29654,1.1658 0.48071,1.73796 0.22942,0.71273 0.48815,1.41677 0.77654,2.10775 0.24637,0.5903 0.52992,1.16463 0.81351,1.73797 0.14177,0.28662 0.21569,0.62634 0.44374,0.85049 0.15725,0.15456 0.37984,0.23455 0.59165,0.29583 0.23799,0.0688 0.49409,0.1074 0.73956,0.0739 0.23587,-0.0322 0.47039,-0.12259 0.6656,-0.25884 0.22915,-0.15994 0.41367,-0.38736 0.55467,-0.62863 0.15144,-0.25915 0.24935,-0.55395 0.29583,-0.85049 0.0802,-0.5116 0.0178,-1.03815 -0.037,-1.55308 -0.0558,-0.52404 -0.16665,-1.04216 -0.29582,-1.55308 -0.12995,-0.51399 -0.32125,-1.01049 -0.48072,-1.5161 -0.19817,-0.62833 -0.38095,-1.26164 -0.59165,-1.88588 -0.19702,-0.5837 -0.44891,-1.1487 -0.62862,-1.73796 -0.14825,-0.48611 -0.22064,-0.99328 -0.36978,-1.47912 -0.15792,-0.51443 -0.35776,-1.0153 -0.55467,-1.5161 -0.27895,-0.70945 -0.61389,-1.39621 -0.88748,-2.10775 -0.20146,-0.52394 -0.35154,-1.06675 -0.55467,-1.59005 -0.23778,-0.61257 -0.58163,-1.1844 -0.77653,-1.81193 -0.0932,-0.30011 -0.12676,-0.61562 -0.18489,-0.92445 -0.0787,-0.41822 -0.16258,-0.83584 -0.22187,-1.25725 -0.0656,-0.46638 -0.061,-0.94228 -0.14791,-1.40517 -0.0519,-0.27625 -0.16117,-0.53907 -0.22187,-0.81351 -0.11072,-0.50058 -0.19391,-1.00755 -0.25885,-1.5161 -0.0736,-0.57673 -0.16621,-1.15684 -0.14791,-1.73797 0.0184,-0.58542 0.17568,-1.15819 0.25884,-1.73797 0.0512,-0.35718 0.10177,-0.71449 0.14792,-1.07236 0.0397,-0.30781 0.11093,-0.92445 0.11093,-0.92445"/><path d="m 228.18901,279.37356 c 0,0 0.5834,1.33809 0.96143,1.95984 0.54944,0.90367 1.10949,1.83334 1.88588,2.55148 0.59755,0.55272 1.32735,0.96273 2.07077,1.29423 0.77317,0.34477 1.61212,0.52834 2.44055,0.70259 0.90071,0.18945 1.81951,0.28892 2.73637,0.36978 0.58987,0.052 1.18291,0.0616 1.77494,0.0739 0.29576,0.006 0.88748,0 0.88748,0"/><path d="m 242.05577,284.95725 c 0,0 0.3989,-0.0417 0.59165,0 0.29112,0.0631 0.56868,0.20011 0.81351,0.36978 0.28655,0.19858 0.48954,0.49659 0.73956,0.73956 0.43771,0.42538 0.90409,0.82125 1.33121,1.25725 0.37251,0.38025 0.78,0.73847 1.07236,1.1833 0.1636,0.24892 0.21929,0.55646 0.36979,0.81351 0.23169,0.39571 0.4971,0.77744 0.81351,1.10934 0.2298,0.24105 0.51386,0.42391 0.77654,0.62863 0.48611,0.37884 0.92549,0.83857 1.47912,1.10934 0.50499,0.24698 1.07592,0.33286 1.62703,0.44374 0.46315,0.0932 0.93288,0.19647 1.40517,0.18489 0.4133,-0.0101 0.85136,-0.0352 1.22027,-0.22187 0.27232,-0.13776 0.49923,-0.3728 0.66561,-0.62863 0.12115,-0.18628 0.20985,-0.40674 0.22187,-0.62862 0.0116,-0.21495 -0.0321,-0.44716 -0.14792,-0.62863 -0.11805,-0.185 -0.3405,-0.27727 -0.51769,-0.40676 -0.33675,-0.24609 -0.69412,-0.46279 -1.03538,-0.70258 -0.27435,-0.19277 -0.58131,-0.34977 -0.81352,-0.59165 -0.277,-0.28854 -0.45436,-0.65876 -0.6656,-0.99841 -0.28584,-0.45959 -0.51639,-0.9528 -0.81352,-1.40516 -0.22738,-0.34616 -0.46913,-0.68472 -0.73956,-0.99841 -0.2504,-0.29046 -0.55178,-0.53323 -0.81352,-0.81351 -0.43527,-0.46611 -0.85125,-0.95033 -1.25725,-1.44215 -0.31865,-0.386 -0.66805,-0.75342 -0.92445,-1.18329 -0.22054,-0.36975 -0.29991,-0.81192 -0.51769,-1.1833 -0.25814,-0.4402 -0.60216,-0.82463 -0.92445,-1.22028 -0.24826,-0.30476 -0.50273,-0.60544 -0.77654,-0.88747 -0.16404,-0.16896 -0.31662,-0.35813 -0.51769,-0.48071 -0.40283,-0.24557 -0.88552,-0.32599 -1.33121,-0.48072 -0.58916,-0.20454 -1.59006,-0.55466 -1.77495,-0.59165 -0.18489,-0.037 -1.22742,-0.57853 -1.8489,-0.85049 -0.94159,-0.41205 -1.8949,-0.79693 -2.84731,-1.1833 -0.58964,-0.2392 -1.18663,-0.46013 -1.77494,-0.70258 -0.34717,-0.14307 -0.73216,-0.22228 -1.03539,-0.44374 -0.19758,-0.1443 -0.3297,-0.36217 -0.48071,-0.55467 -0.22375,-0.28523 -0.45307,-0.5703 -0.62863,-0.88747 -0.0776,-0.14019 -0.15045,-0.28724 -0.18489,-0.44373 -0.0689,-0.31322 0.0297,-0.64773 -0.037,-0.96143 -0.0966,-0.45448 -0.35563,-0.85877 -0.51769,-1.29423 -0.26376,-0.70873 -0.46533,-1.43998 -0.73956,-2.14473 -0.22421,-0.57619 -0.55165,-1.11197 -0.73956,-1.70099 -0.14548,-0.45601 -0.18412,-0.93972 -0.29582,-1.40516 -0.18769,-0.78211 -0.38882,-1.56189 -0.62863,-2.32962 -0.23015,-0.73682 -0.55062,-1.44357 -0.77654,-2.1817 -0.24587,-0.80328 -0.45555,-1.6185 -0.62862,-2.44055 -0.18787,-0.89231 -0.32895,-1.79478 -0.44374,-2.6994 -0.12151,-0.95761 -0.20203,-1.92066 -0.25885,-2.88428 -0.0769,-1.30481 -0.0601,-2.61358 -0.11093,-3.91967 -0.0581,-1.49215 -0.0518,-2.99079 -0.22187,-4.47435 -0.11844,-1.03286 -0.34894,-2.0501 -0.55467,-3.06917 -0.27991,-1.38651 -0.6474,-2.75445 -0.92445,-4.14154 -0.20838,-1.04329 -0.3205,-2.10532 -0.55467,-3.14313 -0.16323,-0.72343 -0.35965,-1.44034 -0.59165,-2.14473 -0.21483,-0.65226 -0.46242,-1.29453 -0.73956,-1.92285 -0.25583,-0.58001 -0.55344,-1.14097 -0.85049,-1.70099 -0.48359,-0.91169 -1.08696,-1.76085 -1.5161,-2.6994 -0.46856,-1.02476 -0.74853,-2.12586 -1.14632,-3.18011 -0.33211,-0.88017 -0.7664,-1.72397 -1.03539,-2.62544 -0.39952,-1.33891 -0.85049,-3.88269 -0.85049,-4.10456 0,-0.22187 -0.39428,-2.90896 -0.59165,-4.36341 -0.27097,-1.99684 -0.60248,-3.98638 -0.81352,-5.99044 -0.10356,-0.98341 -0.12065,-1.97458 -0.22186,-2.95824 -0.10688,-1.03874 -0.27215,-2.07064 -0.40676,-3.10615 -0.0993,-0.76412 -0.17408,-1.53177 -0.29583,-2.29264 -0.22804,-1.42507 -0.60788,-2.824 -0.81351,-4.25247 -0.12705,-0.88256 -0.20938,-1.77214 -0.25885,-2.66242 -0.0486,-0.87389 -0.0682,-1.75076 -0.037,-2.62544 0.0309,-0.86543 0.099,-1.73123 0.22187,-2.58846 0.19443,-1.35677 0.58092,-2.67986 0.81352,-4.03061 0.20707,-1.20251 0.37875,-2.41157 0.51769,-3.62384 0.14651,-1.27833 0.28335,-2.55997 0.3328,-3.84572 0.0502,-1.30565 0.0122,-2.61398 -0.037,-3.91967 -0.0493,-1.30847 -0.15262,-2.61458 -0.25884,-3.91967 -0.1557,-1.91313 -0.38747,-3.81943 -0.55467,-5.73159 -0.0689,-0.78826 -0.008,-1.59542 -0.18489,-2.3666 -0.15121,-0.65809 -0.41607,-1.29318 -0.73956,-1.88588 -0.26223,-0.48046 -0.61048,-0.91115 -0.96143,-1.3312 -0.29623,-0.35456 -0.61854,-0.68875 -0.96143,-0.99841 -0.86009,-0.77674 -1.77979,-1.49049 -2.73637,-2.14473 -0.63862,-0.43678 -1.28389,-0.88273 -1.99682,-1.18329 -0.61164,-0.25786 -1.27963,-0.35383 -1.92286,-0.5177 -1.27761,-0.32548 -2.58662,-0.53338 -3.84571,-0.92445 -1.0843,-0.33678 -2.13653,-0.77298 -3.18011,-1.22027 -1.00339,-0.43006 -1.96723,-0.94731 -2.95824,-1.40517 -1.44743,-0.66873 -2.93281,-1.25582 -4.36341,-1.95983 -2.57294,-1.26617 -5.10827,-2.61453 -7.58049,-4.06758 -1.1614,-0.68261 -2.27449,-1.44443 -3.40198,-2.18171 -0.59513,-0.38916 -1.77495,-1.18329 -1.77495,-1.18329"/><path d="m 182.18835,137.89564 c 0,0 -0.87232,-0.4157 -1.25726,-0.70258 -0.49623,-0.36982 -0.94564,-0.81013 -1.3312,-1.29423 -0.25154,-0.31583 -0.45402,-0.67133 -0.62863,-1.03538 -0.37435,-0.7805 -0.65558,-1.60655 -0.88747,-2.44055 -0.17161,-0.61718 -0.36978,-1.88588 -0.36978,-1.88588"/><path d="m 177.45516,135.60301 c 0,0 -0.17402,-1.77396 -0.14791,-2.66242 0.0222,-0.75649 0.18015,-1.50294 0.25884,-2.25566 0.0682,-0.65262 0.11452,-1.30744 0.18489,-1.95984 0.18642,-1.72829 0.44744,-3.44807 0.62863,-5.17692 0.13156,-1.25526 0.16537,-2.52078 0.3328,-3.77176 0.16614,-1.24134 0.38815,-2.47651 0.66561,-3.6978 0.19544,-0.86023 0.48399,-1.69684 0.70258,-2.55148 0.17262,-0.67489 0.34322,-1.35089 0.48071,-2.0338 0.0148,-0.0735 0.037,-0.22186 0.037,-0.22186"/><path d="m 177.08538,116.2635 c 0,0 0.79887,-2.02748 1.22027,-3.0322 0.36935,-0.88061 0.72623,-1.76788 1.14632,-2.62544 0.27177,-0.55479 0.67449,-1.04713 0.88748,-1.62703 0.23003,-0.62629 0.22127,-1.31894 0.40675,-1.95984 0.11711,-0.40465 0.44374,-1.18329 0.44374,-1.18329"/><path d="m 179.59989,112.048 c 0,0 0.30261,-0.5623 0.55467,-0.73956 0.13714,-0.0964 0.31492,-0.12298 0.48071,-0.14791 0.34129,-0.0513 0.69342,0.0466 1.03538,0 0.45632,-0.0622 0.91028,-0.18293 1.33121,-0.36978 0.40006,-0.17758 0.79406,-0.39897 1.10934,-0.70258 0.34478,-0.33202 0.57799,-0.7666 0.81352,-1.1833 0.36643,-0.64829 0.65881,-1.3381 0.92445,-2.03379 0.14741,-0.38606 0.28154,-0.77959 0.36978,-1.1833 0.10349,-0.47347 0.0728,-0.97063 0.18489,-1.44214 0.10279,-0.43237 0.29534,-0.83834 0.44374,-1.25725 0.19657,-0.5549 0.45366,-1.09172 0.59165,-1.66401 0.19818,-0.82192 0.33716,-1.669041 0.3328,-2.514508 -0.002,-0.435784 -0.23718,-1.764884 -0.23718,-1.764884"/><path d="m 180.32619,110.16635 c 0,0 -0.40297,0.53048 -0.52295,0.83672 -0.13594,0.34697 -0.14966,0.73033 -0.20917,1.09819 -0.0842,0.5208 -0.1182,1.04917 -0.20918,1.56884 -0.1415,0.80829 -0.34122,1.60536 -0.52295,2.40557 -0.15075,0.66382 -0.27952,1.33386 -0.47066,1.9872 -0.20743,0.70902 -0.40646,1.42871 -0.73212,2.09179 -0.3666,0.74645 -0.88198,1.41106 -1.35967,2.09179 -0.51467,0.73343 -1.02513,1.47508 -1.62114,2.14409 -0.72172,0.81011 -1.52559,1.54717 -2.35326,2.24868 -0.79786,0.67625 -1.59736,1.37203 -2.51016,1.88261 -0.70344,0.39347 -1.48928,0.61888 -2.24867,0.88902 -0.7064,0.25129 -1.40486,0.55461 -2.14409,0.67983 -0.60178,0.10194 -1.22191,0.10097 -1.83032,0.0523 -0.74292,-0.0594 -1.46998,-0.25164 -2.19638,-0.41836 -0.91493,-0.20999 -1.84895,-0.38051 -2.71933,-0.73212 -0.70173,-0.28348 -1.38571,-0.63886 -1.98721,-1.09819 -0.69561,-0.53119 -1.22892,-1.24673 -1.83032,-1.88262 -0.81379,-0.86045 -1.6982,-1.66487 -2.40556,-2.61474 -0.44817,-0.60183 -0.85661,-1.24448 -1.15048,-1.93491 -0.28321,-0.66539 -0.39302,-1.39198 -0.57525,-2.09179 -0.27594,-1.05967 -0.6036,-2.11002 -0.78442,-3.18999 -0.19076,-1.13937 -0.22031,-2.30001 -0.31377,-3.45145 -0.0198,-0.24386 -0.0523,-0.73213 -0.0523,-0.73213"/><path d="m 150.9888,115.13436 c 0,0 -0.66865,-1.5822 -1.0459,-2.35327 -0.24334,-0.49737 -0.54692,-0.96406 -0.78442,-1.46425 -0.3888,-0.81883 -0.78373,-1.64245 -1.0459,-2.51016 -0.1849,-0.61197 -0.2843,-1.24857 -0.36606,-1.88261 -0.0693,-0.53706 -0.0142,-1.08723 -0.10459,-1.62114 -0.0543,-0.32108 -0.26148,-0.94131 -0.26148,-0.94131"/><path d="m 149.41995,111.6829 c 0,0 -0.59948,-0.56086 -0.9413,-0.78442 -0.0652,-0.0427 -0.134,-0.084 -0.20918,-0.10459 -0.23596,-0.0647 -0.4926,-0.002 -0.73213,-0.0523 -0.30765,-0.0641 -0.62532,-0.14283 -0.88901,-0.31377 -0.4035,-0.26158 -0.70897,-0.65831 -0.9936,-1.04589 -0.42492,-0.57861 -0.77293,-1.21866 -1.0459,-1.88262 -0.17208,-0.41856 -0.25461,-0.86876 -0.36607,-1.30737 -0.15414,-0.60656 -0.29571,-1.21661 -0.41835,-1.83032 -0.1213,-0.607 -0.19284,-1.22323 -0.31377,-1.83031 -0.0768,-0.3857 -0.20639,-0.76109 -0.26148,-1.15049 -0.1272,-0.899 -0.21692,-1.813368 -0.15688,-2.719331 0.0305,-0.460516 0.17035,-0.907224 0.26147,-1.359665 0.0668,-0.331798 0.20918,-0.993602 0.20918,-0.993602"/><path d="m 181.2675,106.6626 c 0.36022,0.16255 0.66127,-0.46145 0.88901,-0.78443 0.27048,-0.38359 0.39041,-0.85711 0.52295,-1.30737 0.18052,-0.61327 0.30477,-1.24627 0.36606,-1.88261 0.0368,-0.38173 -0.0631,-0.77221 0,-1.15049 0.10603,-0.63619 0.36872,-1.23956 0.62754,-1.830314 0.29421,-0.671543 0.64364,-1.321949 1.0459,-1.934909 0.34056,-0.518951 0.69961,-1.037628 1.15048,-1.464255 0.15456,-0.146246 0.31057,-0.379045 0.52295,-0.366064 0.23408,0.01431 0.34815,0.314308 0.52295,0.470654 0.15645,0.139936 0.30657,0.287445 0.47065,0.418358 0.11722,0.09352 0.24264,0.346632 0.36607,0.261474 0.28189,-0.19449 -0.19948,-0.656782 -0.26148,-0.993601 -0.0889,-0.482768 -0.17912,-0.973881 -0.15688,-1.464255 0.0403,-0.887928 0.41435,-1.73256 0.52295,-2.614742 0.13433,-1.091198 0.05,-2.200341 0.15688,-3.294573 0.13871,-1.420616 0.52267,-2.812368 0.62754,-4.235881 0.064,-0.869225 0.10011,-1.748929 0,-2.614741 -0.13161,-1.138272 -0.43156,-2.256699 -0.78442,-3.346869 -0.3898,-1.20429 -0.90008,-2.370631 -1.46426,-3.503753 -0.64761,-1.3007 -1.27869,-2.638699 -2.19638,-3.765227 -0.72504,-0.890036 -1.67365,-1.574413 -2.56245,-2.300973 -1.17687,-0.962048 -2.34493,-1.958092 -3.66063,-2.71933 -1.13523,-0.656822 -2.37898,-1.11189 -3.60835,-1.568845 -1.54007,-0.572441 -3.08216,-1.217411 -4.70653,-1.464255 -1.49934,-0.227844 -3.0331,0 -4.54965,0 -1.56884,0 -3.14576,-0.158999 -4.70653,0 -1.20398,0.122653 -2.42011,0.3147 -3.55605,0.732127 -1.36197,0.500486 -2.65656,1.221381 -3.81752,2.091793 -0.71007,0.532363 -1.28676,1.224919 -1.88262,1.882614 -0.75677,0.835308 -1.49364,1.69422 -2.14409,2.614741 -0.56414,0.79837 -1.04807,1.652148 -1.51655,2.510152 -0.49315,0.903192 -0.90294,1.849474 -1.35966,2.771625 -0.57088,1.152657 -1.29137,2.240736 -1.72573,3.451459 -0.28988,0.807982 -0.35673,1.680022 -0.57524,2.510151 -0.21761,0.826699 -0.56465,1.619563 -0.73213,2.457857 -0.19574,0.97973 -0.2426,1.984252 -0.31377,2.980805 -0.0659,0.922184 -0.11662,1.847171 -0.10459,2.771625 0.0107,0.820883 0.14026,1.637072 0.15688,2.457857 0.0152,0.749608 -0.21606,1.517019 -0.0523,2.248677 0.12771,0.570556 0.47269,1.074207 0.78442,1.568845 0.21194,0.33629 0.47759,0.635991 0.73213,0.941307 0.41899,0.502577 1.00121,0.885976 1.30737,1.464255 0.2354,0.444634 0.23176,0.979401 0.36606,1.464251 0.11187,0.40388 0.31015,0.78745 0.36607,1.20279 0.0838,0.62216 -0.0826,1.25556 -0.0523,1.88261 0.0271,0.5615 0.0188,1.14451 0.20918,1.67343 0.077,0.21385 0.21596,0.40459 0.36607,0.57525 0.17983,0.20446 0.40033,0.67301 0.62753,0.52294 0.45556,-0.30092 -0.40881,-1.02638 -0.47065,-1.56884 -0.0613,-0.53802 -0.0135,-1.09267 0.10459,-1.62114 0.13483,-0.60339 0.47073,-1.14389 0.67983,-1.72573 0.26661,-0.74183 0.66612,-1.463159 0.73213,-2.248676 0.0797,-0.948238 -0.4159,-1.872343 -0.41836,-2.823921 -0.002,-0.616299 0.12506,-1.229307 0.26148,-1.830319 0.14156,-0.623664 0.45897,-1.201449 0.57524,-1.830319 0.15558,-0.841486 0.15688,-2.300972 0.15688,-2.562446 0,-0.261474 0.57525,-3.189984 0.57525,-3.399163 0,-0.20918 0.30686,-1.386112 0.57524,-2.039499 0.50691,-1.234123 1.03168,-2.521823 1.93491,-3.503753 0.7659,-0.832626 1.76712,-1.478846 2.82392,-1.882613 0.80599,-0.307942 1.70051,-0.405162 2.56244,-0.366064 0.68003,0.03085 1.34143,0.255349 1.98721,0.470653 0.70354,0.23456 1.32171,0.702547 2.0395,0.889012 0.69502,0.18055 1.42681,0.243437 2.14408,0.20918 0.72735,-0.03474 1.42172,-0.326624 2.14409,-0.418359 0.86619,-0.109998 1.74291,-0.108935 2.61474,-0.156884 0.69708,-0.03834 1.77803,-0.10459 2.0918,-0.10459 0.31376,0 2.09179,0.0523 2.35326,0.0523 0.26148,0 1.13304,0.488623 1.67344,0.784422 0.68723,0.376175 1.40741,0.728163 1.9872,1.255076 0.50575,0.459622 0.9385,1.015491 1.25508,1.621139 0.29626,0.566768 0.44344,1.20452 0.57524,1.830319 0.16266,0.772306 0.16504,1.569931 0.26147,2.353267 0.0795,0.645956 0.20483,1.286547 0.26148,1.934909 0.0759,0.868967 -0.12384,1.772905 0.10459,2.614741 0.15521,0.57199 0.78442,1.359666 0.83671,1.568845 0.0523,0.20918 0.39387,0.856109 0.52295,1.30737 0.13636,0.476687 0.2537,0.96851 0.26148,1.464255 0.0113,0.722219 -0.27546,1.422796 -0.31377,2.144088 -0.0472,0.888441 0.0111,1.78226 0.10459,2.66703 0.0967,0.91483 0.32047,1.81175 0.47065,2.71933 0.10948,0.66161 0.26131,1.31866 0.31377,1.98721 0.0232,0.29543 -0.2701,0.76712 1e-5,0.88901 z"/><path d="m 156.95041,116.65091 c 0,0 0.62577,0.0943 0.9413,0.10459 0.38369,0.0125 0.76783,-0.0216 1.15049,-0.0523 0.45477,-0.0365 0.90481,-0.12159 1.35967,-0.15688 0.43483,-0.0337 0.87352,-0.0969 1.30737,-0.0523 0.21448,0.0221 0.41426,0.12521 0.62753,0.15689 0.34528,0.0513 0.69694,0.0436 1.0459,0.0523 0.38338,0.01 0.76709,0.009 1.15049,0 0.38379,-0.009 0.7671,-0.0721 1.15048,-0.0523 0.35206,0.0182 0.69678,0.10793 1.0459,0.15688 0.40041,0.0561 0.80137,0.10841 1.20278,0.15689 0.31342,0.0378 0.94131,0.10459 0.94131,0.10459"/><path d="m 158.0486,117.38304 c 0,0 0.82354,0.54532 1.25507,0.78442 0.66147,0.36651 1.31698,0.77036 2.0395,0.9936 0.57235,0.17684 1.17936,0.24016 1.77803,0.26147 0.69878,0.0249 1.4122,0.008 2.09179,-0.15688 0.47829,-0.1158 0.90958,-0.37623 1.35966,-0.57524 0.45653,-0.20186 0.90977,-0.41131 1.35967,-0.62754 0.21079,-0.10131 0.62754,-0.31377 0.62754,-0.31377"/><path d="m 157.73483,115.86649 c 0,0 0.8297,-0.27137 1.25508,-0.36607 0.77488,-0.17251 1.56479,-0.27374 2.35326,-0.36606 0.65996,-0.0773 1.32299,-0.13882 1.98721,-0.15689 0.71464,-0.0194 1.42979,0.0226 2.14408,0.0523 0.2966,0.0123 0.59752,-0.004 0.88902,0.0523 0.43303,0.0834 0.85893,0.22461 1.25507,0.41836 0.50814,0.24852 1.41196,0.94131 1.41196,0.94131"/><path d="m 160.92481,110.37553 c 0,0 -0.55191,-0.22651 -0.67983,-0.47065 -0.0728,-0.13897 -0.10279,-0.35214 0,-0.47066 0.0808,-0.0931 0.24342,-0.0647 0.36606,-0.0523 0.25783,0.026 0.50323,0.14 0.73213,0.26147 0.28642,0.15199 0.54731,0.35408 0.78442,0.57525 0.21707,0.20248 0.34185,0.4964 0.57525,0.67983 0.24517,0.19268 0.52737,0.37909 0.83671,0.41836 0.2476,0.0314 0.5219,-0.0224 0.73213,-0.15689 0.22025,-0.14092 0.30939,-0.42172 0.47066,-0.62754 0.1528,-0.19502 0.27087,-0.42872 0.47065,-0.57524 0.15139,-0.11103 0.34863,-0.13945 0.52295,-0.20918 0.17432,-0.0697 0.33615,-0.19038 0.52295,-0.20918 0.19391,-0.0195 0.40261,0.0141 0.57524,0.10459 0.13102,0.0687 0.26481,0.1742 0.31377,0.31377 0.0523,0.14895 0.038,0.34118 -0.0523,0.47066 -0.11147,0.15986 -0.52295,0.26147 -0.52295,0.26147"/><path d="m 167.30478,110.84618 c 0,0 0.74942,-0.0584 1.0459,-0.26147 0.29926,-0.20498 0.48807,-0.55417 0.62754,-0.88901 0.1157,-0.27779 0.16577,-0.58823 0.15688,-0.88902 -0.0111,-0.37613 -0.12432,-0.74778 -0.26147,-1.09819 -0.11663,-0.29799 -0.47066,-0.83671 -0.47066,-0.83671"/><path d="m 160.0881,110.6893 c 0,0 -0.62016,-0.0664 -0.88902,-0.20918 -0.27236,-0.14466 -0.52255,-0.36226 -0.67983,-0.62754 -0.14662,-0.24729 -0.20379,-0.54928 -0.20918,-0.83672 -0.006,-0.3384 0.0601,-0.68972 0.20918,-0.9936 0.20149,-0.4108 0.88901,-1.04589 0.88901,-1.04589"/><path d="m 166.36348,98.661489 c 0,0 -0.36955,1.067606 -0.47066,1.621141 -0.1194,0.65365 -0.13826,1.323 -0.15688,1.9872 -0.0215,0.76689 -0.0872,1.54657 0.0523,2.30097 0.0943,0.50964 0.52295,1.46426 0.52295,1.46426"/><path d="m 162.0753,98.870668 c 0,0 -0.0752,1.640982 -0.15688,2.457862 -0.077,0.77025 -0.18363,1.5379 -0.31377,2.30097 -0.11668,0.68411 -0.41836,2.0395 -0.41836,2.0395"/><path d="m 168.45527,100.80558 c 0,0 -0.003,-0.69915 0.15688,-0.993605 0.21258,-0.390282 0.63585,-0.625336 0.9936,-0.889012 0.24546,-0.180917 0.49354,-0.37919 0.78443,-0.470653 0.48339,-0.151988 1.00997,-0.116472 1.51655,-0.10459 0.7544,0.0177 1.50412,0.1387 2.24867,0.261474 0.49252,0.08121 1.00441,0.119592 1.46426,0.313769 0.4632,0.195592 1.25507,0.836717 1.25507,0.836717"/><path d="m 168.82133,99.655091 c 0,0 0.17242,0.345869 0.31377,0.470649 0.17533,0.15478 0.40747,0.23463 0.62754,0.31377 0.43769,0.1574 0.89458,0.30693 1.35966,0.31377 0.53325,0.008 1.06441,-0.14069 1.56885,-0.31377 0.36869,-0.1265 0.76436,-0.25338 1.0459,-0.522945 0.12963,-0.124117 0.21645,-0.296923 0.26147,-0.470654 0.0175,-0.0675 0.021,-0.142678 0,-0.209179 -0.064,-0.202936 -0.36606,-0.522948 -0.36606,-0.522948"/><path d="m 427.92981,98.518146 c 0.28134,0.664976 -0.0297,1.432113 -0.69464,1.713454 -0.66497,0.28133 -1.43211,-0.0297 -1.71345,-0.694646 -0.14177,-0.335091 -0.13748,-0.714103 0.0118,-1.045903" transform="translate(-255.08051,-0.05229482)"/><path d="m 427.54247,98.381928 c 0.23635,0.307739 0.17848,0.748809 -0.12926,0.985158 -0.30774,0.236349 -0.74881,0.178475 -0.98516,-0.129264 -0.19619,-0.255444 -0.19355,-0.611574 0.006,-0.864089" transform="translate(-255.44657,0)"/><path d="m 159.5913,100.57025 c 0,0 0.0167,-0.35376 -0.0261,-0.52295 -0.0545,-0.215412 -0.17506,-0.4098 -0.28762,-0.601389 -0.12985,-0.221016 -0.25272,-0.457462 -0.44451,-0.627538 -0.17799,-0.157839 -0.41275,-0.237645 -0.62754,-0.339916 -0.24697,-0.117595 -0.49072,-0.256831 -0.75827,-0.313769 -0.31554,-0.06715 -0.64492,-0.03235 -0.96746,-0.02615 -0.53271,0.01024 -1.06803,0.02587 -1.59499,0.10459 -0.45163,0.06747 -0.88928,0.208034 -1.33352,0.313769 -0.47094,0.112092 -1.41196,0.339916 -1.41196,0.339916"/><path d="m 153.99575,98.530751 c 0,0 -0.1883,0.112808 -0.20918,0.20918 -0.0158,0.07277 0.0294,0.153138 0.0784,0.209179 0.1823,0.208362 0.47979,0.278306 0.73213,0.392211 0.36447,0.164521 0.73689,0.319398 1.12434,0.418359 0.58877,0.150383 1.19979,0.198278 1.80417,0.26147 0.26928,0.0282 0.54055,0.0721 0.81057,0.0523 0.12445,-0.009 0.25644,-0.0188 0.36606,-0.07844 0.0758,-0.04123 0.13929,-0.108664 0.18304,-0.183032 0.0644,-0.109374 0.10243,-0.239182 0.10454,-0.366064 0.002,-0.143721 -0.10454,-0.418359 -0.10454,-0.418359"/><path d="m 158.30972,98.537952 c 0.0154,0.684116 -0.45396,1.26645 -1.09393,1.418443 m -0.94752,-0.101436 c -0.4678,-0.225002 -0.79543,-0.698426 -0.80789,-1.252964 -0.003,-0.142389 0.015,-0.284453 0.0539,-0.421457"/><path d="m 412.81365,98.14145 c 0.2475,0.305936 0.20012,0.754583 -0.10581,1.00208 -0.30594,0.247498 -0.75458,0.200124 -1.00208,-0.105812 -0.21092,-0.260721 -0.21148,-0.633233 -0.001,-0.894591" transform="translate(-255.44657,0)"/><path d="m 167.72314,96.883465 c 0.44051,0.201329 0.80268,-0.559154 1.25508,-0.732127 0.64822,-0.247846 1.34905,-0.348274 2.03949,-0.418359 0.5723,-0.05809 1.15128,-0.03015 1.72573,0 0.66515,0.03491 1.33572,0.07062 1.98721,0.209179 0.71712,0.152516 1.37392,0.530878 2.09179,0.679833 0.36005,0.07471 0.82613,0.351974 1.09819,0.10459 0.27084,-0.24627 0.0681,-0.738521 0,-1.098192 -0.0976,-0.51524 -0.27586,-1.033717 -0.57524,-1.464255 -0.25372,-0.364875 -0.58459,-0.715161 -0.9936,-0.889012 -0.43433,-0.184617 -0.94092,-0.07537 -1.41196,-0.104589 -0.6968,-0.04322 -1.39759,-0.17851 -2.0918,-0.10459 -0.73581,0.07835 -1.42192,0.413862 -2.14408,0.575243 -0.67407,0.150635 -1.45423,-7.06e-4 -2.0395,0.366064 -0.40181,0.251803 -0.6273,0.725044 -0.83672,1.150486 -0.13642,0.277133 -0.24592,0.580515 -0.26147,0.889012 -0.0143,0.283406 -0.10121,0.718761 0.15688,0.836717 z"/><path d="m 161.55235,96.517401 c 0.32877,-0.558159 -0.35338,-1.29446 -0.78442,-1.778024 -0.38991,-0.437418 -0.98789,-0.636262 -1.51655,-0.889012 -0.62215,-0.297447 -1.26834,-0.555401 -1.93491,-0.732127 -0.64821,-0.171859 -1.31787,-0.27246 -1.9872,-0.313769 -0.52225,-0.03223 -1.05195,-0.0289 -1.56885,0.0523 -0.7522,0.11816 -1.49911,0.321638 -2.19638,0.627538 -0.33674,0.147731 -0.72865,0.275253 -0.94131,0.575243 -0.14434,0.203612 -0.13945,0.483154 -0.15688,0.732127 -0.0171,0.244067 -0.11056,0.549546 0.0523,0.732128 0.18889,0.211762 0.55465,0.12592 0.83672,0.156884 0.52012,0.0571 1.04854,0.10757 1.56885,0.0523 0.42882,-0.04555 0.83259,-0.227328 1.25507,-0.313769 0.43238,-0.08846 0.86743,-0.174206 1.30737,-0.209179 0.48655,-0.03868 0.98,-0.06096 1.46426,0 0.76764,0.09663 1.52377,0.304832 2.24867,0.575243 0.32868,0.122609 0.61975,0.33043 0.94131,0.470653 0.27304,0.119065 0.54152,0.27396 0.83672,0.313769 0.19081,0.02573 0.47751,0.113589 0.57523,-0.0523 z"/><path d="m 398.80032,185.62778 c 0,1.17903 -1.21748,2.13482 -2.71933,2.13482 -1.50184,0 -2.71933,-0.95579 -2.71933,-2.13482 0,-1.17903 1.21749,-2.13482 2.71933,-2.13482 1.50185,0 2.71933,0.95579 2.71933,2.13482 z" transform="matrix(0.88250632,-0.47030053,0.47030053,0.88250632,-295.89663,208.40096)"/><path d="m 396.86543,186.49065 c 0,0.47654 -0.38632,0.86286 -0.86287,0.86286 -0.47654,0 -0.86286,-0.38632 -0.86286,-0.86286 0,-0.47655 0.38632,-0.86287 0.86286,-0.86287 0.47655,0 0.86287,0.38632 0.86287,0.86287 z" transform="translate(-255.39428,-0.10458965)"/><path d="m 445.36788,185.49704 c 0,1.12063 -1.20533,2.02908 -2.69219,2.02908 -1.48686,0 -2.69219,-0.90845 -2.69219,-2.02908 0,-1.12063 1.20533,-2.02908 2.69219,-2.02908 1.48686,0 2.69219,0.90845 2.69219,2.02908 z" transform="matrix(0.82397712,0.56662307,-0.56662307,0.82397712,-72.68009,-217.76018)"/><path d="m 443.617,186.35991 c 0,0.51987 -0.42144,0.94131 -0.94131,0.94131 -0.51987,0 -0.94131,-0.42144 -0.94131,-0.94131 0,-0.51987 0.42144,-0.94131 0.94131,-0.94131 0.51987,0 0.94131,0.42144 0.94131,0.94131 z" transform="translate(-255.44657,0)"/><path d="m 86.619334,237.23943 c 0,0 3.314104,2.54581 5.26822,2.57285 1.973644,0.0273 5.390737,-2.45033 5.390737,-2.45033" transform="translate(71.989627,62.034365)"/><path d="m 93.043217,179.70755 c 0,0.90907 -0.736946,1.64602 -1.646015,1.64602 -0.90907,0 -1.646016,-0.73695 -1.646016,-1.64602 0,-0.90907 0.736946,-1.64602 1.646016,-1.64602 0.909069,0 1.646015,0.73695 1.646015,1.64602 z" transform="translate(72.162892,62.034365)"/></g></g></g></defs></svg>
<div class="placement-grid">
<figure class="placement-card"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 420 490" role="img" aria-labelledby="limbs-title limbs-desc" font-family="system-ui, sans-serif">
<title id="limbs-title" data-i18n="s91">Electrodes on arms and leg</title><desc id="limbs-desc" data-i18n="s92">Front view. RA on the right forearm, LA on the left forearm and RL on the right leg. The body's right side is on the left of the image.</desc>
<rect width="420" height="490" rx="14" fill="#ffffff"/><svg x="100" y="25" width="220" height="440" viewBox="0 267 330 768"><use href="#commons-front-body"/></svg>
<path d="M85 178 H125 L153 220" fill="none" stroke="#d43f50" stroke-width="2" stroke-linecap="round"/>
<circle cx="153" cy="220" r="12" fill="white" stroke="#d43f50" stroke-width="2"/>
<circle cx="153" cy="220" r="7" fill="#d43f50"/>
<rect x="25" y="164" width="60" height="28" rx="8" fill="#d43f50"/>
<text x="55" y="184" text-anchor="middle" fill="white" font-size="17" font-weight="700">RA</text><path d="M335 178 H290 L260 220" fill="none" stroke="#e8c434" stroke-width="2" stroke-linecap="round"/>
<circle cx="260" cy="220" r="12" fill="white" stroke="#e8c434" stroke-width="2"/>
<circle cx="260" cy="220" r="7" fill="#e8c434"/>
<rect x="335" y="164" width="60" height="28" rx="8" fill="#e8c434"/>
<text x="365" y="184" text-anchor="middle" fill="#253544" font-size="17" font-weight="700">LA</text><path d="M85 344 H150 V295 H180" fill="none" stroke="#21895c" stroke-width="2" stroke-linecap="round"/>
<circle cx="180" cy="295" r="12" fill="white" stroke="#21895c" stroke-width="2"/>
<circle cx="180" cy="295" r="7" fill="#21895c"/>
<rect x="25" y="330" width="60" height="28" rx="8" fill="#21895c"/>
<text x="55" y="350" text-anchor="middle" fill="white" font-size="17" font-weight="700">RL</text>
</svg></figure>
<figure class="placement-card"><svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 420 490" role="img" aria-labelledby="torso-title torso-desc" font-family="system-ui, sans-serif">
<title id="torso-title" data-i18n="s96">Electrodes on chest and abdomen</title><desc id="torso-desc" data-i18n="s97">Front view. RA on the right and LA on the left below the collarbone. RL on the lower right abdomen above the hip. The body's right side is on the left of the image.</desc>
<rect width="420" height="490" rx="14" fill="#ffffff"/><svg x="100" y="25" width="220" height="440" viewBox="0 267 330 768"><use href="#commons-front-body"/></svg>
<path d="M85 138 H148 L180 144" fill="none" stroke="#d43f50" stroke-width="2" stroke-linecap="round"/>
<circle cx="180" cy="144" r="12" fill="white" stroke="#d43f50" stroke-width="2"/>
<circle cx="180" cy="144" r="7" fill="#d43f50"/>
<rect x="25" y="124" width="60" height="28" rx="8" fill="#d43f50"/>
<text x="55" y="144" text-anchor="middle" fill="white" font-size="17" font-weight="700">RA</text><path d="M335 138 H272 L240 144" fill="none" stroke="#e8c434" stroke-width="2" stroke-linecap="round"/>
<circle cx="240" cy="144" r="12" fill="white" stroke="#e8c434" stroke-width="2"/>
<circle cx="240" cy="144" r="7" fill="#e8c434"/>
<rect x="335" y="124" width="60" height="28" rx="8" fill="#e8c434"/>
<text x="365" y="144" text-anchor="middle" fill="#253544" font-size="17" font-weight="700">LA</text><path d="M85 308 H165 V222 H180" fill="none" stroke="#21895c" stroke-width="2" stroke-linecap="round"/>
<circle cx="180" cy="222" r="12" fill="white" stroke="#21895c" stroke-width="2"/>
<circle cx="180" cy="222" r="7" fill="#21895c"/>
<rect x="25" y="294" width="60" height="28" rx="8" fill="#21895c"/>
<text x="55" y="314" text-anchor="middle" fill="white" font-size="17" font-weight="700">RL</text>
</svg></figure>
</div>
</dialog>
<script>
)HTML"
#include "translations.h"
R"HTML(

const archiveViewer=document.getElementById('archive-viewer');
const archiveViewport=document.getElementById('archive-viewport');
const archiveLarge=document.getElementById('archive-large');
const archiveZoomEl=document.getElementById('archive-zoom');
let archiveView={url:null,opener:null,zoom:1,baseWidth:800,drag:null};
function setArchiveZoom(percent,x=archiveViewport.clientWidth/2,y=archiveViewport.clientHeight/2){
 const next=Math.max(1,Math.min(4,Number(percent)/100));
 if(!Number.isFinite(next))return;
 const ratio=next/archiveView.zoom;
 const scrollX=(archiveViewport.scrollLeft||0)+(x||0),scrollY=(archiveViewport.scrollTop||0)+(y||0);
 archiveView.zoom=next;archiveLarge.style.width=archiveView.baseWidth*next+'px';
 archiveZoomEl.value=String(Math.round(next*100));document.getElementById('archive-zoom-label').textContent=Math.round(next*100)+' %';
 archiveViewport.scrollLeft=scrollX*ratio-(x||0);archiveViewport.scrollTop=scrollY*ratio-(y||0);
}
function openArchiveImage(url,title,opener){
 archiveView={url,opener,zoom:1,baseWidth:800,drag:null};
 archiveLarge.src=url;document.getElementById('archive-viewer-title').textContent=title;
 if(!archiveViewer.open)archiveViewer.showModal();
 archiveView.baseWidth=archiveViewport.clientWidth||800;
 archiveViewport.scrollLeft=0;archiveViewport.scrollTop=0;setArchiveZoom(100);
}
function closeArchiveImage(url){if(archiveViewer.open && archiveView.url===url)archiveViewer.close();}
document.getElementById('archive-close').addEventListener('click',()=>archiveViewer.close());
archiveViewer.addEventListener('close',()=>{archiveLarge.removeAttribute('src');archiveView.url=null;archiveView.drag=null;if(archiveView.opener)archiveView.opener.focus();});
archiveViewer.addEventListener('click',event=>{
 if(event.target!==archiveViewer)return;
 const r=archiveViewer.getBoundingClientRect();if(event.clientX<r.left||event.clientX>r.right||event.clientY<r.top||event.clientY>r.bottom)archiveViewer.close();
});
archiveZoomEl.addEventListener('input',()=>setArchiveZoom(archiveZoomEl.value));
document.getElementById('archive-zoom-in').addEventListener('click',()=>setArchiveZoom(archiveView.zoom*100+25));
document.getElementById('archive-zoom-out').addEventListener('click',()=>setArchiveZoom(archiveView.zoom*100-25));
document.getElementById('archive-fit').addEventListener('click',()=>{archiveView.baseWidth=archiveViewport.clientWidth||800;setArchiveZoom(100);archiveViewport.scrollLeft=0;archiveViewport.scrollTop=0;});
archiveViewport.addEventListener('wheel',event=>{
 if(!event.ctrlKey)return;event.preventDefault();const r=archiveViewport.getBoundingClientRect();
 setArchiveZoom(archiveView.zoom*100+(event.deltaY<0?25:-25),event.clientX-r.left,event.clientY-r.top);
},{passive:false});
archiveViewport.addEventListener('pointerdown',event=>{
 if(event.button!==0||event.pointerType==='touch')return;
 archiveView.drag={x:event.clientX,y:event.clientY,left:archiveViewport.scrollLeft||0,top:archiveViewport.scrollTop||0};
 archiveViewport.setPointerCapture(event.pointerId);event.preventDefault();
});
archiveViewport.addEventListener('pointermove',event=>{const d=archiveView.drag;if(!d)return;archiveViewport.scrollLeft=d.left+d.x-event.clientX;archiveViewport.scrollTop=d.top+d.y-event.clientY;});
for(const eventName of ['pointerup','pointercancel','lostpointercapture'])archiveViewport.addEventListener(eventName,()=>{archiveView.drag=null;});
const helpDialog=document.getElementById('electrode-help');
const helpOpen=document.getElementById('electrode-help-open');
helpOpen.addEventListener('click',()=>{if(!helpDialog.open)helpDialog.showModal();});
document.getElementById('electrode-help-close').addEventListener('click',()=>helpDialog.close());
helpDialog.addEventListener('close',()=>helpOpen.focus());
helpDialog.addEventListener('click',event=>{
 if(event.target!==helpDialog)return;
 const bounds=helpDialog.getBoundingClientRect();
 if(event.clientX<bounds.left || event.clientX>bounds.right || event.clientY<bounds.top || event.clientY>bounds.bottom)helpDialog.close();
});
const canvas=document.getElementById('plot'),ctx=canvas.getContext('2d');
const statusEl=document.getElementById('status');
let paused=false,latest=null,baseline=1650;
const viewEl=document.getElementById('view-mode');
const live={values:[],timingMissing:[],first:0,next:0,interval:10000,cursor:null,sweepOrigin:0,lastFrame:null};
const DISPLAY_BUFFER_SECONDS=0.55;
function resetPlayback(){
 if(!live.values.length)return;
 live.cursor=Math.max(live.first,live.next-1-DISPLAY_BUFFER_SECONDS*1e6/live.interval);
 live.sweepOrigin=live.cursor;
 live.lastFrame=null;
}
function collectLive(data){
 const first=data.total-data.values.length;
 if(!data.values.length)return;
 if(!live.values.length || data.total<live.next || first>live.next || data.intervalUs!==live.interval){
  live.values=data.values.slice();live.timingMissing=(data.timingMissing||data.values.map(()=>false)).slice();live.first=first;live.next=data.total;live.interval=data.intervalUs;
  resetPlayback();return;
 }
 const offset=Math.max(0,live.next-first);
 live.values.push(...data.values.slice(offset));
 live.timingMissing.push(...(data.timingMissing||data.values.map(()=>false)).slice(offset));live.next=data.total;
 // Keep history longer than the visible window, including during brief buffering.
 const excess=Math.max(0,live.values.length-Math.ceil(30e6/live.interval));
 if(excess){live.values.splice(0,excess);live.timingMissing.splice(0,excess);live.first+=excess;}
 if(!paused && (live.cursor<live.first || (viewEl.value!=='sweep' && live.next-1-live.cursor>2e6/live.interval)))resetPlayback();
}
viewEl.addEventListener('change',()=>{live.sweepOrigin=live.cursor||0;if(latest)draw(latest);});
function advancePlayback(timestamp){
 const previous=live.lastFrame;live.lastFrame=timestamp;
 if(paused || live.cursor===null || previous===null)return;
 const elapsed=Math.min(0.1,Math.max(0,(timestamp-previous)/1000));
 const lag=(live.next-1-live.cursor)*live.interval/1e6;
 // Slight playback speed corrections absorb Wi-Fi jitter without packet jumps.
 const speed=Math.max(0.9,Math.min(1.1,1+(lag-DISPLAY_BUFFER_SECONDS)*0.3));
 live.cursor=Math.min(live.next-1,live.cursor+elapsed*1e6/live.interval*speed);
}
function animate(timestamp){
 advancePlayback(timestamp);
 checkHeartFreshness();
 if(!paused && latest)draw(latest);
 requestAnimationFrame(animate);
}
const gainEl=document.getElementById('gain');
const voltageEl=document.getElementById('voltage-mode');
let measurement={gain:1100,referenceMv:1650};
function voltageFactor(){return voltageEl.value==='ecg'?measurement.gain:1;}
function scaleDescription(units,center,factor,reference){
 return t('scale',{units:(units/factor).toFixed(3),center:((center-reference)/factor).toFixed(3)});
}
function setVoltageMode(mode){
 voltageEl.value=mode;
 const choices=mode==='ecg'?['0.2','0.1','0.05','0.02']:['200','100','50','20'];
 gainEl.replaceChildren();
 for(const value of choices){const option=document.createElement('option');option.value=value;option.textContent=localizedNumber(Number(value))+t('square');gainEl.append(option);}
 gainEl.value=choices[1];
}
voltageEl.addEventListener('change',()=>{setVoltageMode(voltageEl.value);if(latest)draw(latest);});
const autoHeightEl=document.getElementById('auto-height');
const autoCenterEl=document.getElementById('center');
function fitHeight(values,cells){
 values=values.filter(Number.isFinite);
 if(!values.length)return {units:100,center:1650};
 let min=Infinity,max=-Infinity;
 for(const value of values){min=Math.min(min,value);max=Math.max(max,value);}
 // Leave 10% at the top and bottom; a minimum span limits amplification of small fluctuations.
 return {units:Math.max(32,max-min)/(Math.max(1,cells)*0.8),center:(min+max)/2};
}
function resolveScale(values,cells,manualUnits,fixedCenter,zoom,centered){
 values=values.filter(Number.isFinite);
 const center=centered && values.length?fitHeight(values,cells).center:fixedCenter;
 let units=manualUnits;
 if(zoom && values.length){
  let radius=16;
  for(const value of values)radius=Math.max(radius,Math.abs(value-center));
  units=2*radius/(Math.max(1,cells)*0.8);
 }
 return {units,center};
}
autoHeightEl.addEventListener('change',()=>{
 gainEl.disabled=autoHeightEl.checked;
 if(latest)draw(latest);
});
gainEl.addEventListener('change',()=>{if(latest)draw(latest);});
autoCenterEl.addEventListener('change',()=>{if(latest)draw(latest);});
document.getElementById('pause').addEventListener('click',()=>{
 paused=!paused;
 document.getElementById('pause').textContent=paused?t('resume'):t('s26');
 if(!paused)resetPlayback();
 statusEl.textContent=paused?t('paused'):t('live');
});
// Visual connectors only: underlying null values remain missing.
function timingBridgeSegments(values,timingMissing,dt,from=0,to=values.length-1){
 const maxGap=timingGapLimits(dt).maxSamples,segments=[],end=Math.min(to,values.length-1);
 for(let i=from;i<=end;){
  if(Number.isFinite(values[i])||!timingMissing[i]){i++;continue;}
  const start=i;while(i<=end&&!Number.isFinite(values[i])&&timingMissing[i])i++;
  if(i-start<=maxGap && start>from && i<=end && Number.isFinite(values[start-1]) && Number.isFinite(values[i]))segments.push([start-1,i]);
 }
 return segments;
}
function draw(data){
 const w=canvas.clientWidth,h=canvas.clientHeight,dpr=window.devicePixelRatio||1;
 const pixelWidth=Math.round(w*dpr),pixelHeight=Math.round(h*dpr);
 if(canvas.width!==pixelWidth || canvas.height!==pixelHeight){canvas.width=pixelWidth;canvas.height=pixelHeight;}
 ctx.setTransform(dpr,0,0,dpr,0,0);
 const left=64,right=w-12,top=22,bottom=h-32,width=right-left,height=bottom-top;
 // Use equal horizontal and vertical grid spacing; on smaller displays
 // shorten the time window to keep the fine grid readable.
 const span=Math.min(4.99,width/6*0.04),cell=width/span*0.04;
 let units=Number(gainEl.value)*voltageFactor(),center=baseline;
 const values=live.values,dt=live.interval/1e6;
 const cursor=live.cursor===null?live.first:live.cursor;
 const sweep=viewEl.value==='sweep';
 const mid=(top+bottom)/2;
 // Grid and signal share the same interpolated playback cursor.
 // Modulo one large square preserves the phase of the major grid lines.
 const gridPhase=sweep?0:((cursor*dt/0.04)%5+5)%5;
 ctx.fillStyle='#fffafa';ctx.fillRect(0,0,w,h);
 ctx.save();ctx.beginPath();ctx.rect(left,top,width,height);ctx.clip();
 const grid=(major)=>{
  ctx.strokeStyle=major?'#d89299':'#f0cdd0';ctx.lineWidth=major?1:0.5;ctx.beginPath();
  for(let i=-5;i<=Math.ceil(width/cell)+5;i++){
   if((i%5===0)!==major)continue;
   const x=right-(i+gridPhase)*cell;ctx.moveTo(x,top);ctx.lineTo(x,bottom);
  }
  const n=Math.ceil(height/cell);
  for(let i=-n;i<=n;i++){
   if((i%5===0)!==major)continue;
   const y=mid+i*cell;ctx.moveTo(left,y);ctx.lineTo(right,y);
  }
  ctx.stroke();
 };
 grid(false);grid(true);
 const cycleStart=live.sweepOrigin+Math.floor(Math.max(0,(cursor-live.sweepOrigin)*dt)/span)*span/dt;
 const start=sweep?cycleStart:cursor-span/dt;
 if(autoHeightEl.checked || autoCenterEl.checked){
  // Evaluate a complete time window rather than only the new sweep segment
  // to stabilize scaling when wrapping to the next screen.
  const visible=values.slice(Math.max(0,Math.ceil(cursor-span/dt-1-live.first)),Math.max(0,Math.ceil(cursor)-live.first+1));
  const fit=resolveScale(visible,height/cell,units,baseline,autoHeightEl.checked,autoCenterEl.checked);units=fit.units;center=fit.center;
 }
 ctx.strokeStyle='#242b35';ctx.lineWidth=1.6;ctx.lineJoin='round';ctx.beginPath();
 let started=false,clipped=false;
 const plotPoint=(seq,v)=>{
  if(!Number.isFinite(v)){started=false;return;}
  const x=sweep?left+(seq-cycleStart)*dt/span*width:right-(cursor-seq)*dt/span*width;
  const y=mid-(v-center)/units*cell;
  if(y<top || y>bottom)clipped=true;
  if(started)ctx.lineTo(x,y);else{ctx.moveTo(x,y);started=true;}
 };
 const from=Math.max(0,Math.ceil((sweep?cycleStart:start-1)-live.first));
 const to=Math.min(values.length-1,Math.floor(cursor-live.first));
 for(let i=from;i<=to;i++)plotPoint(live.first+i,values[i]);
 const index=Math.floor(cursor)-live.first,fraction=cursor-Math.floor(cursor);
 if(index>=0 && index+1<values.length && fraction>0 && Number.isFinite(values[index]) && Number.isFinite(values[index+1])){
  plotPoint(cursor,values[index]+(values[index+1]-values[index])*fraction);
 }
 ctx.stroke();
 ctx.strokeStyle='rgba(0,0,0,0.9)';ctx.beginPath();
 for(const [a,b] of timingBridgeSegments(values,live.timingMissing,dt,from,to)){
  const seqA=live.first+a,seqB=live.first+b;
  const x=seq=>sweep?left+(seq-cycleStart)*dt/span*width:right-(cursor-seq)*dt/span*width;
  ctx.moveTo(x(seqA),mid-(values[a]-center)/units*cell);
  ctx.lineTo(x(seqB),mid-(values[b]-center)/units*cell);
 }
 ctx.stroke();
 if(sweep){
  const head=left+(cursor-cycleStart)*dt/span*width;
  ctx.strokeStyle='#59817b';ctx.lineWidth=1;ctx.beginPath();ctx.moveTo(head,top);ctx.lineTo(head,bottom);ctx.stroke();
 }
 ctx.restore();
 ctx.font='11px system-ui';ctx.fillStyle='#74464c';ctx.textAlign='right';
 const axisFactor=voltageFactor(),axisReference=voltageEl.value==='ecg'?measurement.referenceMv:0;
 const labelStep=Math.max(5,Math.ceil(32/(cell*5))*5);
 const decimals=Math.max(0,Math.min(4,Math.ceil(-Math.log10(units*labelStep/axisFactor))+1));
 for(let i=-Math.ceil(height/cell/2);i<=Math.ceil(height/cell/2);i++){
  if(i%labelStep!==0)continue;
  const y=mid-i*cell;if(y<top+5 || y>bottom-5)continue;
  const value=(center+i*units-axisReference)/axisFactor;
  ctx.fillText((Math.abs(value)<0.5*10**(-decimals)?0:value).toLocaleString(locale(),{minimumFractionDigits:decimals,maximumFractionDigits:decimals,useGrouping:false}),left-8,y+4);
 }
 ctx.textAlign='left';ctx.fillText(voltageEl.value==='ecg'?'mV ≈':'mV',4,13);
 ctx.font='12px system-ui';ctx.fillStyle='#74464c';
 ctx.fillText(sweep?'0 s':'-'+span.toFixed(2)+' s',left,h-10);ctx.fillText(sweep?span.toFixed(2)+' s':t('now'),right-40,h-10);
 const caption=(sweep?t('sweep'):t('s21'))+t('grid')+scaleDescription(units,center,voltageFactor(),voltageEl.value==='ecg'?measurement.referenceMv:0)+(voltageEl.value==='ecg'?t('ecgUnit'):t('outputUnit'))+(live.values.some((v,i)=>live.first+i>=cursor-span/dt && live.first+i<=cursor && Number.isFinite(v) && (v>=2500 || v<=0))?t('adcLimit'):'')+(clipped?t('outOfView'):'');
 const captionEl=document.getElementById('caption');if(captionEl.textContent!==caption)captionEl.textContent=caption;
}
// Sequence numbers prevent duplicate values from overlapping ESP buffers.
let archiveCursor=null,archiveInterval=null,pending=[],segmentSettings=null;
let archiveSerial=0,archiveSkipped=0,archiveWarning='';
const archiveEntries=[];
const lengthEl=document.getElementById('segment-length');
const progressEl=document.getElementById('archive-progress');
function updateProgress(){
 const target=Math.round(Number(lengthEl.value)*0.2*1e6/(archiveInterval||10000));
 progressEl.textContent=t('archiveProgress',{count:pending.length,target,images:archiveEntries.length})+(archiveSkipped?t('archiveSkipped',{count:archiveSkipped}):'')+(archiveWarning?' · '+t(archiveWarning):'');
}
function archiveLayout(values,settings){
 const dt=settings.interval/1e6,perRow=Math.max(1,Math.round(5/dt));
 const fit=resolveScale(values,30,settings.units,settings.baseline,settings.autoHeight,settings.autoCenter);
 return {dt,perRow,units:fit.units,center:fit.center};
}
function hasVisibleArchiveCurve(values,settings){
 const {dt,perRow,units,center}=archiveLayout(values,settings);
 if(!(dt>0) || !(units>0) || !Number.isFinite(units) || !Number.isFinite(center))return false;
 if(settings.timingMissing){
  const connected=values.slice();
  for(const [a,b] of timingBridgeSegments(values,settings.timingMissing,dt))if(Math.floor(a/perRow)===Math.floor(b/perRow))for(let i=a+1;i<b;i++)connected[i]=values[a]+(values[b]-values[a])*(i-a)/(b-a);
  values=connected;
 }
 const halfRange=15*units;
 let runSeconds=0;
 for(let i=1;i<values.length;i++){
  // Do not connect traces across SVG row boundaries.
  if(i%perRow===0 || !Number.isFinite(values[i-1]) || !Number.isFinite(values[i])){runSeconds=0;continue;}
  const a=values[i-1]-center,b=values[i]-center,difference=b-a;
  let enter=0,exit=1;
  if(difference===0){
   if(Math.abs(a)>halfRange){runSeconds=0;continue;}
  }else{
   const t1=(-halfRange-a)/difference,t2=(halfRange-a)/difference;
   enter=Math.max(0,Math.min(t1,t2));exit=Math.min(1,Math.max(t1,t2));
   if(exit<=enter){runSeconds=0;continue;}
  }
  if(enter>0)runSeconds=0;
  runSeconds+=dt*(exit-enter);
  // Brief contact flashes should not create practically empty images.
  if(runSeconds+1e-9>=0.5)return true;
  if(exit<1)runSeconds=0;
 }
 return false;
}
function archiveSvg(values,settings,partial){
 // Fixed resolution, five seconds per row, independent of the phone screen.
 const {dt,perRow,units,center}=archiveLayout(values,settings);
 const rows=Math.ceil(values.length/perRow),W=1100,rowHeight=260,H=90+rows*rowHeight;
 const cell=8,scale=cell/0.04;
 const factor=settings.factor||1,reference=settings.reference||0;
 const label=settings.started.toLocaleString(locale());
 let svg=`<svg xmlns="http://www.w3.org/2000/svg" width="${W}" height="${H}" viewBox="0 0 ${W} ${H}"><defs><pattern id="fine" width="8" height="8" patternUnits="userSpaceOnUse"><path d="M 8 0 H 0 V 8" fill="none" stroke="#f0cdd0" stroke-width="0.6"/></pattern><pattern id="grid" width="40" height="40" patternUnits="userSpaceOnUse"><rect width="40" height="40" fill="url(#fine)"/><path d="M 40 0 H 0 V 40" fill="none" stroke="#d89299" stroke-width="1"/></pattern></defs><rect width="100%" height="100%" fill="#fffafa"/><g font-family="sans-serif" fill="#402b30"><text x="40" y="26" font-size="18">HeartMonitor · ${label} · ${t('segment')} ${archiveSerial}${partial?t('partial'):''}</text><text x="40" y="48" font-size="13">${t('exportScale',{count:values.length,duration:(values.length*dt).toFixed(2),units:(units/factor).toFixed(3),center:((center-reference)/factor).toFixed(3)})}${settings.autoHeight?' · '+t('s23'):''}${settings.autoCenter?t('centered'):''}</text><text x="40" y="68" font-size="13">${settings.ecg?t('exportGain',{gain:factor}):t('exportOutput')}${t('exportTiming')}${values.some(v=>Number.isFinite(v) && (v>=2500 || v<=0))?t('adcLimit'):''}${values.some(v=>!Number.isFinite(v))?t('exportGaps',{count:values.filter(v=>!Number.isFinite(v)).length}):''}</text></g>`;
 for(let row=0;row<rows;row++){
  const part=values.slice(row*perRow,(row+1)*perRow),y=90+row*rowHeight,mid=y+120;
  const traces=[];let points=[];
  part.forEach((v,i)=>{
   if(!Number.isFinite(v)){if(points.length)traces.push(points.join(' '));points=[];return;}
   points.push(`${(40+i*dt*scale).toFixed(2)},${(mid-(v-center)/units*cell).toFixed(2)}`);
  });
  if(points.length)traces.push(points.join(' '));
  const missing=(settings.timingMissing||[]).slice(row*perRow,(row+1)*perRow);
  const connectors=timingBridgeSegments(part,missing,dt).map(([a,b])=>`<line data-timing-gap="true" clip-path="url(#clip${row})" x1="${(40+a*dt*scale).toFixed(2)}" y1="${(mid-(part[a]-center)/units*cell).toFixed(2)}" x2="${(40+b*dt*scale).toFixed(2)}" y2="${(mid-(part[b]-center)/units*cell).toFixed(2)}" stroke="#000" stroke-opacity="0.9" stroke-width="1.5"/>`).join('');
  const lines=traces.map(trace=>`<polyline clip-path="url(#clip${row})" points="${trace}" fill="none" stroke="#242b35" stroke-width="1.5" stroke-linejoin="round"/>`).join('');
  svg+=`<defs><clipPath id="clip${row}"><rect x="40" y="${y}" width="1000" height="240"/></clipPath></defs><rect x="40" y="${y}" width="1000" height="240" fill="url(#grid)"/>${lines}${connectors}<text x="40" y="${y+255}" font-family="sans-serif" font-size="12" fill="#74464c">${(row*perRow*dt).toFixed(2)} s</text>`;
 }
 return svg+'</svg>';
}
function saveSegment(partial=false){
 if(!pending.length)return;
 // Check visibility using the same scale and row layout as the export.
 if(!hasVisibleArchiveCurve(pending,segmentSettings)){++archiveSkipped;pending=[];segmentSettings=null;updateProgress();return;}
 ++archiveSerial;
 const svg=archiveSvg(pending,segmentSettings,partial);
 const url=URL.createObjectURL(new Blob([svg],{type:'image/svg+xml;charset=utf-8'}));
 const card=document.createElement('article');card.className='archive-card';
 const heading=document.createElement('div');
 heading.textContent=t('archiveHeading',{serial:archiveSerial,date:segmentSettings.started.toLocaleString(locale()),duration:(pending.length*segmentSettings.interval/1e6).toFixed(2)});
 const preview=document.createElement('img');preview.src=url;preview.alt=t('archiveAlt',{serial:archiveSerial});preview.loading='lazy';
 const link=document.createElement('a');link.className='download';link.href=url;
 link.download='HeartMonitor-'+segmentSettings.started.toISOString().replace(/[:.]/g,'-')+'-'+archiveSerial+'.svg';link.textContent=t('download');
 const previewButton=document.createElement('button');previewButton.type='button';previewButton.className='archive-preview';previewButton.setAttribute('aria-label',t('enlarge',{serial:archiveSerial}));
 previewButton.append(preview);previewButton.addEventListener('click',()=>openArchiveImage(url,heading.textContent,previewButton));
 const remove=document.createElement('button');remove.type='button';remove.textContent=t('remove');
 const entry={card,url,heading,preview,previewButton,link,remove,serial:archiveSerial,started:segmentSettings.started,duration:(pending.length*segmentSettings.interval/1e6).toFixed(2)};
 remove.addEventListener('click',()=>{closeArchiveImage(url);card.remove();URL.revokeObjectURL(url);archiveEntries.splice(archiveEntries.indexOf(entry),1);updateProgress();});
 card.append(heading,previewButton,link,remove);document.getElementById('archive-list').prepend(card);archiveEntries.push(entry);
 if(archiveEntries.length>20){const oldest=archiveEntries.shift();closeArchiveImage(oldest.url);oldest.card.remove();URL.revokeObjectURL(oldest.url);}
 pending=[];segmentSettings=null;updateProgress();
}
function collectArchive(data){
 const first=data.total-data.values.length;
 if(archiveCursor!==null && (data.total<archiveCursor || data.intervalUs!==archiveInterval || first>archiveCursor)){
  saveSegment(true);
  archiveWarning='interruption';
  archiveCursor=null;
 }
 archiveInterval=data.intervalUs;
 // On the first request, accept only the latest value; do not archive earlier data.
 if(archiveCursor===null)archiveCursor=Math.max(first,data.total-1);
 const start=Math.max(0,archiveCursor-first);
 const target=Math.max(1,Math.round(Number(lengthEl.value)*0.2*1e6/data.intervalUs));
 for(let i=start;i<data.values.length;i++){
  if(!pending.length)segmentSettings={interval:data.intervalUs,units:Number(gainEl.value)*voltageFactor(),baseline,factor:voltageFactor(),reference:voltageEl.value==='ecg'?measurement.referenceMv:0,ecg:voltageEl.value==='ecg',autoHeight:autoHeightEl.checked,autoCenter:autoCenterEl.checked,started:new Date(),timingMissing:[]};
  pending.push(data.values[i]);
  segmentSettings.timingMissing.push(!!(data.timingMissing&&data.timingMissing[i]));
  if(pending.length>=target)saveSegment();
 }
 archiveCursor=data.total;updateProgress();
}
lengthEl.addEventListener('change',()=>{saveSegment(true);updateProgress();});
document.getElementById('finish').addEventListener('click',()=>saveSegment(true));
// Store display preferences only, not measurements or pause state.
const SETTINGS_COOKIE='heartmonitor_settings';
const beatSmoothingEl=document.getElementById('beat-smoothing');
const beatReferenceEl=document.getElementById('beat-reference');
const beatMeanEl=document.getElementById('beat-mean'),beatMedianEl=document.getElementById('beat-median');
function saveSettings(){
 const settings={version:3,language:currentLanguage,voltage:voltageEl.value,view:viewEl.value,gain:gainEl.value,autozoom:autoHeightEl.checked,center:autoCenterEl.checked,segment:lengthEl.value,beatSmoothing:beatSmoothingEl.checked,beatReference:beatReferenceEl.checked,beatMean:beatMeanEl.checked,beatMedian:beatMedianEl.checked};
 try{
  document.cookie=SETTINGS_COOKIE+'='+encodeURIComponent(JSON.stringify(settings))+'; Max-Age=31536000; Path=/; SameSite=Lax';
 }catch(error){/* The display also works when cookies are blocked. */}
}
function restoreSettings(){
 try{
  const cookie=(document.cookie||'').split(';').map(part=>part.trim()).find(part=>part.startsWith(SETTINGS_COOKIE+'='));
  if(!cookie)return;
  const settings=JSON.parse(decodeURIComponent(cookie.slice(SETTINGS_COOKIE.length+1)));
  if(!settings || ![1,2,3].includes(settings.version))return;
  if(SUPPORTED_LANGUAGES.includes(settings.language))currentLanguage=settings.language;
  if(['scroll','sweep'].includes(settings.view))viewEl.value=settings.view;
  if(settings.version===3){
   setVoltageMode(settings.voltage==='output'?'output':'ecg');
   const valid=voltageEl.value==='ecg'?['0.2','0.1','0.05','0.02']:['200','100','50','20'];
   if(valid.includes(settings.gain))gainEl.value=settings.gain;
  }
  if(typeof settings.autozoom==='boolean')autoHeightEl.checked=settings.autozoom;
  if(typeof settings.center==='boolean')autoCenterEl.checked=settings.center;
  if(typeof settings.beatSmoothing==='boolean')beatSmoothingEl.checked=settings.beatSmoothing;
  if(typeof settings.beatReference==='boolean')beatReferenceEl.checked=settings.beatReference;
  if(typeof settings.beatMean==='boolean')beatMeanEl.checked=settings.beatMean;
  if(typeof settings.beatMedian==='boolean')beatMedianEl.checked=settings.beatMedian;
  if(['25','50','100'].includes(settings.segment))lengthEl.value=settings.segment;
 }catch(error){/* Invalid or older cookies leave default settings unchanged. */}
 gainEl.disabled=autoHeightEl.checked;
}
restoreSettings();
gainEl.disabled=autoHeightEl.checked;
for(const control of [viewEl,voltageEl,gainEl,autoHeightEl,autoCenterEl,lengthEl,beatSmoothingEl,beatReferenceEl,beatMeanEl,beatMedianEl])control.addEventListener('change',saveSettings);
updateProgress();
const beatDialog=document.getElementById('beat-dialog'),beatOpen=document.getElementById('beat-open');
beatSmoothingEl.addEventListener('change',()=>drawBeatOverlay());
beatReferenceEl.addEventListener('change',()=>drawBeatOverlay());
for(const control of [beatMeanEl,beatMedianEl])control.addEventListener('change',()=>drawBeatOverlay());
beatOpen.addEventListener('click',()=>{if(!beatDialog.open)beatDialog.showModal();drawBeatOverlay();});
document.getElementById('beat-close').addEventListener('click',()=>beatDialog.close());
beatDialog.addEventListener('close',()=>beatOpen.focus());
beatDialog.addEventListener('click',event=>{
 if(event.target!==beatDialog)return;
 const bounds=beatDialog.getBoundingClientRect();
 if(event.clientX<bounds.left || event.clientX>bounds.right || event.clientY<bounds.top || event.clientY>bounds.bottom)beatDialog.close();
});
window.addEventListener('resize' ,()=>{if(latest)draw(latest);drawBeatOverlay();});
// Experimental polarity-independent peak detection; no rhythm diagnosis.
function median(values){
 if(!values.length)return 0;
 const sorted=values.slice().sort((a,b)=>a-b),middle=Math.floor(sorted.length/2);
 return sorted.length%2?sorted[middle]:(sorted[middle-1]+sorted[middle])/2;
}
function timingGapLimits(dt){
 const milliseconds=)HTML" HM_STRINGIFY(HEART_MAX_TIMING_GAP_MS) R"HTML(;
 const percent=)HTML" HM_STRINGIFY(HEART_MAX_TIMING_GAP_PERCENT) R"HTML(;
 return {maxSamples:Math.floor(milliseconds/1000/dt+1e-9),maxSeconds:milliseconds/1000,maxFraction:percent/100};
}
// Internally bridge only isolated timing gaps for beat timing analysis.
// Contact gaps and raw waveforms remain unchanged.
function prepareTimingAnalysis(values,timingMissing,dt){
 const limits=timingGapLimits(dt),prepared=values.slice(),maxGap=limits.maxSamples;
 let filled=0;
 for(let i=0;i<values.length;){
  if(Number.isFinite(values[i])||!timingMissing[i]){i++;continue;}
  const start=i;while(i<values.length&&!Number.isFinite(values[i])&&timingMissing[i])i++;
  const count=i-start;
  if(count>maxGap||start===0||i===values.length||!Number.isFinite(values[start-1])||!Number.isFinite(values[i]))continue;
  filled+=count;
  for(let j=0;j<count;j++)prepared[start+j]=values[start-1]+(values[i]-values[start-1])*(j+1)/(count+1);
 }
 return filled/Math.max(1,values.length)<=limits.maxFraction?prepared:values.slice();
}
function detectHeartbeats(values,first,intervalUs,timingMissing=[]){
 const minSeconds=)HTML" HM_STRINGIFY(HEART_MIN_SIGNAL_SECONDS) R"HTML(;
 const minBeats=)HTML" HM_STRINGIFY(HEART_MIN_BEATS) R"HTML(;
 const dt=intervalUs/1e6;
 const empty=reason=>({bpm:null,arrow:'—',trend:t('s5'),peaks:[],reason});
 if(!(dt>0) || dt>0.02)return empty(t('rateLow'));
 values=prepareTimingAnalysis(values,timingMissing,dt);
 // Contact gaps and prolonged clipping split the sequence. Brief peaks
 // remain unchanged: no reconstruction or amplitude correction.
 const clipped=value=>value<=20 || value>=2480;
 const maxClipSamples=Math.max(1,Math.floor(0.08/dt));
 let start=0,clipRun=0;
 for(let i=0;i<values.length;i++){
  const value=values[i];
  if(!Number.isFinite(value) || value<0 || value>3600){start=i+1;clipRun=0;continue;}
  clipRun=clipped(value)?clipRun+1:0;
  if(clipRun>maxClipSamples)start=i+1;
 }
 const signal=values.slice(start);
 if(signal.length*dt<minSeconds)return empty(t('collectSignal',{seconds:minSeconds}));
 const clippedCount=signal.reduce((count,value)=>count+(clipped(value)?1:0),0);
 if(clippedCount/signal.length>0.15)return empty(t('tooClipped'));
 let min=Infinity,max=-Infinity;
 signal.forEach(v=>{min=Math.min(min,v);max=Math.max(max,v);});
 if(max-min<50)return empty(t('weak'));
 // Subtract the local DC component, then lightly smooth three points for detection only.
 const radius=Math.max(2,Math.round(0.12/dt)),prefix=[0];
 for(const value of signal)prefix.push(prefix[prefix.length-1]+value);
 const detrended=signal.map((value,i)=>{
  const a=Math.max(0,i-radius),b=Math.min(signal.length,i+radius+1);
  return value-(prefix[b]-prefix[a])/(b-a);
 });
 const filtered=detrended.map((value,i)=>(detrended[Math.max(0,i-1)]+value+detrended[Math.min(signal.length-1,i+1)])/3);
 const magnitude=filtered.map(Math.abs),noise=median(magnitude);
 const mad=median(magnitude.map(v=>Math.abs(v-noise)));
 const sorted=magnitude.slice().sort((a,b)=>a-b);
 const threshold=Math.max(25,noise+6*mad,sorted[Math.floor((sorted.length-1)*0.98)]*0.35);
 const candidates=[];
 const margin=Math.ceil(0.2/dt);
 for(let i=margin;i<magnitude.length-margin;i++){
  const amplitude=magnitude[i];
  if(amplitude<threshold || amplitude<=magnitude[i-1] || amplitude<magnitude[i+1])continue;
  let left=i,right=i;
  while(left>0 && magnitude[left-1]>amplitude*0.35)--left;
  while(right+1<magnitude.length && magnitude[right+1]>amplitude*0.35)++right;
  const width=(right-left+1)*dt;
  if(width>=0.02 && width<=0.14)candidates.push({index:i,amplitude});
 }
 // Keep only the strongest peak within 280 ms, allowing either polarity.
 const selected=[];
 for(const peak of candidates.sort((a,b)=>b.amplitude-a.amplitude)){
  if(selected.every(other=>Math.abs(other.index-peak.index)*dt>=0.28))selected.push(peak);
 }
 selected.sort((a,b)=>a.index-b.index);
 const peaks=selected.map(peak=>first+start+peak.index);
 if(peaks.length<minBeats)return {...empty(t('waitBeats',{count:minBeats})),peaks};
 const rr=peaks.slice(1).map((peak,i)=>(peak-peaks[i])*dt);
 const recent=rr.slice(-4),typical=median(recent);
 if(recent.some(value=>value<60/210 || value>60/35 || Math.abs(value-typical)>typical*0.25)){
  return {...empty(t('irregular')),peaks};
 }
 if((first+values.length-1-peaks[peaks.length-1])*dt>Math.max(2,typical*1.8)){
  return {...empty(t('noSequence')),peaks};
 }
 let arrow='—',trend=t('s5');
 if(rr.length>=6){
  const current=60/median(rr.slice(-3)),previous=60/median(rr.slice(-6,-3));
  const difference=current-previous,limit=Math.max(2,previous*0.03);
  arrow=difference>limit?'↑':difference<-limit?'↓':'→';
  trend=arrow==='↑'?t('rising'):arrow==='↓'?t('falling'):t('steady');
 }
 return {bpm:Math.round(60/typical),arrow,trend,peaks,reason:t('estimated',{count:recent.length})+(clippedCount?t('briefClipping'):'')};
}
const heart={beats:[],totalBeats:0,lastPeak:-Infinity,peaks:[],lastSequence:null,lastArrival:0,bpm:null,expired:false};
function hideHeartRate(reason){
 heart.hiddenReason=reason;heart.bpm=null;
 document.getElementById('pulse-value').textContent='—';
 const arrow=document.getElementById('pulse-trend');arrow.textContent='—';arrow.title=t('noTrend');
 document.getElementById('pulse-note').textContent=t(reason);
}
function resetHeartAnalysis(clearOverlay=false){
 heart.lastPeak=-Infinity;heart.peaks=[];heart.lastSequence=null;heart.expired=false;
 if(clearOverlay){heart.beats=[];heart.totalBeats=0;drawBeatOverlay();}
 hideHeartRate('newSequence');
}
function updateHeartAnalysis(data){
 if(heart.lastSequence===data.total){checkHeartFreshness();return;}
 if(heart.lastSequence!==data.total){heart.lastArrival=Date.now();heart.lastSequence=data.total;heart.expired=false;}
 if(data.contactFault || (data.contactFault===undefined && data.leadStatus)){hideHeartRate('checkContact');return;}
 if(data.contactReady===false){hideHeartRate('contactWait');return;}
 // Twenty seconds cover ten beats at 35/min, including margins.
 const analysisStart=Math.max(0,live.values.length-Math.ceil(20e6/live.interval));
 const result=detectHeartbeats(live.values.slice(analysisStart),live.first+analysisStart,live.interval,live.timingMissing.slice(analysisStart));
 heart.peaks=result.peaks;
 heart.bpm=result.bpm;heart.hiddenReason=null;
 const arrow=document.getElementById('pulse-trend');arrow.textContent=result.arrow;arrow.title=result.trend;
 document.getElementById('pulse-value').textContent=result.bpm===null?'—':result.bpm;
 document.getElementById('pulse-note').textContent=result.reason+' · '+result.trend.toLowerCase();
 // Collect new overlays only for a sufficiently clear beat sequence.
 if(result.bpm===null)return;
 const dt=live.interval/1e6;
 for(const peak of result.peaks.slice(-5)){
  if(peak<=heart.lastPeak+Math.ceil(0.28/dt) || peak+Math.ceil(0.45/dt)>=live.next)continue;
  const wave=[];let clipped=false,missingCount=0,missingRun=0,maxMissingRun=0;
  // 1000 points/s: peak exactly at index 250, window from -250 to +450 ms.
  const sampleStep=0.001,pre=0.25,pointCount=701;
  const gapLimits=timingGapLimits(sampleStep);
  for(let step=0;step<pointCount;step++){
   let position=peak+(-pre+step*sampleStep)/dt-live.first;
   if(Math.abs(position-Math.round(position))<1e-7)position=Math.round(position);
   const index=Math.floor(position),fraction=position-index;
   if(index<0 || index>=live.values.length || (fraction && index+1>=live.values.length)){wave.length=0;break;}
   const a=live.values[index],b=fraction?live.values[index+1]:a;
   if(!Number.isFinite(a)||!Number.isFinite(b)){
    const timingOnly=(Number.isFinite(a)||live.timingMissing[index])&&(Number.isFinite(b)||live.timingMissing[index+(fraction?1:0)]);
    if(!timingOnly){wave.length=0;break;}
    wave.push(null);missingCount++;maxMissingRun=Math.max(maxMissingRun,++missingRun);continue;
   }
   missingRun=0;if(a<=20||a>=2480||b<=20||b>=2480)clipped=true;
   wave.push(a+(b-a)*fraction);
  }
  if(wave.length!==pointCount||missingCount/pointCount>gapLimits.maxFraction||maxMissingRun*sampleStep>gapLimits.maxSeconds+Math.max(0,dt-sampleStep)+1e-9)continue;
  const zero=median(wave.slice(0,100).filter(Number.isFinite));
  const sample=wave.map(value=>Number.isFinite(value)?(value-zero)/measurement.gain:null);
  sample.missingCount=missingCount;
  sample.clipped=clipped;sample.intervalSeconds=sampleStep;sample.preSeconds=pre;heart.beats.push(sample);
  if(heart.beats.length>100)heart.beats.shift();
  ++heart.totalBeats;heart.lastPeak=peak;
 }
 if(beatDialog.open)drawBeatOverlay();
}
function checkHeartFreshness(){
 if(heart.lastSequence!==null && !heart.expired && Date.now()-heart.lastArrival>3000){
  heart.expired=true;hideHeartRate('staleRate');
 }
}
const measureEl=document.getElementById('beat-measure');
const measureDefaults=[-220,-120,-40,40,140,360];
const measureState={marks:measureDefaults.slice(),available:false,drag:null,geometry:null,changed:false};
const measureFields=measureDefaults.map((value,i)=>{const field=document.getElementById('measure-'+i);field.value=String(value);return field;});
function measureIntervals(m){return {P:m[1]-m[0],PR:m[2]-m[0],PRsegment:m[2]-m[1],QRS:m[3]-m[2],ST:m[4]-m[3],T:m[5]-m[4],QT:m[5]-m[2]};}
function setMeasureMark(index,value){
 if(!Number.isInteger(index)||index<0||index>5||!Number.isFinite(value))return false;
 const min=index?measureState.marks[index-1]+1:-250,max=index<5?measureState.marks[index+1]-1:450;
 measureState.marks[index]=Math.max(min,Math.min(max,Math.round(value)));measureState.changed=true;return true;
}
function updateMeasurement(mean){
 measureState.available=mean.length>0;
 const active=measureEl.checked&&measureState.available;
 document.getElementById('beat-overlay').className=active?'measuring':'';
 measureFields.forEach((field,i)=>{field.disabled=!active;if(document.activeElement!==field)field.value=String(measureState.marks[i]);});
 const out=document.getElementById('measure-results');
 if(!measureEl.checked){out.textContent=t('s81');return;}
 if(!measureState.available){measureState.drag=null;out.textContent=t('noMean');return;}
 const d=measureIntervals(measureState.marks);
 out.textContent=(measureState.changed?t('measureChanged'):t('measureExample'))+d.P+t('prInterval')+d.PR+t('prSegment')+d.PRsegment+' ms · QRS '+d.QRS+t('stSegment')+d.ST+' ms · T '+d.T+t('qtInterval')+d.QT+' ms';
}
measureEl.addEventListener('change',()=>{measureState.drag=null;if(measureEl.checked){beatMeanEl.checked=true;saveSettings();}drawBeatOverlay();});
measureFields.forEach((field,i)=>field.addEventListener('change',()=>{if(measureEl.checked&&measureState.available){setMeasureMark(i,Number(field.value));field.value=String(measureState.marks[i]);drawBeatOverlay();}}));
document.getElementById('measure-reset').addEventListener('click',()=>{measureState.marks=measureDefaults.slice();measureState.changed=false;drawBeatOverlay();});
const measureCanvas=document.getElementById('beat-overlay');
function markerPointerX(event){const rect=measureCanvas.getBoundingClientRect();return (event.clientX-rect.left)*measureCanvas.clientWidth/(rect.width||rect.right-rect.left);}
measureCanvas.addEventListener('pointerdown',event=>{
 if(!measureEl.checked||!measureState.available||!measureState.geometry||(event.button!==undefined&&event.button!==0))return;
 const x=markerPointerX(event),g=measureState.geometry;
 let index=-1,distance=19;
 measureState.marks.forEach((ms,i)=>{const delta=Math.abs(x-(g.left+(g.right-g.left)*(ms+250)/700));if(delta<distance){distance=delta;index=i;}});
 if(index<0)return;
 measureState.drag=index;measureCanvas.setPointerCapture(event.pointerId);event.preventDefault();
});
measureCanvas.addEventListener('pointermove',event=>{
 if(measureState.drag===null||!measureEl.checked||!measureState.available)return;
 const g=measureState.geometry;setMeasureMark(measureState.drag,(markerPointerX(event)-g.left)/(g.right-g.left)*700-250);
 event.preventDefault();drawBeatOverlay();
});
for(const eventName of ['pointerup','pointercancel','lostpointercapture'])measureCanvas.addEventListener(eventName,()=>{measureState.drag=null;});
function beatStatistics(beats,includeMedian=true){
 if(!beats.length)return {mean:[],median:[],sd:[]};
 const mean=[],middle=[],sd=[];
 for(let i=0;i<beats[0].length;i++){
  const values=beats.map(beat=>beat[i]).filter(Number.isFinite);
  if(!values.length){mean.push(null);middle.push(null);sd.push(null);continue;}
  const average=values.reduce((sum,value)=>sum+value,0)/values.length;
  mean.push(average);if(includeMedian)middle.push(median(values));
  sd.push(values.length>1?Math.sqrt(values.reduce((sum,value)=>sum+(value-average)**2,0)/(values.length-1)):0);
 }
 for(const curve of [mean,middle]){curve.intervalSeconds=beats[0].intervalSeconds;curve.preSeconds=beats[0].preSeconds;}
 return {mean,median:middle,sd};
}
let beatDisplayCache=null;
function beatDisplayData(){
 if(beatDisplayCache && beatDisplayCache.source===heart.beats && beatDisplayCache.total===heart.totalBeats && beatDisplayCache.smooth===beatSmoothingEl.checked)return beatDisplayCache;
 const displayed=beatSmoothingEl.checked?heart.beats.map(smoothBeatDisplay):heart.beats;
 const statistics=beatStatistics(displayed);
 beatDisplayCache={source:heart.beats,total:heart.totalBeats,smooth:beatSmoothingEl.checked,displayed,statistics,raw:beatSmoothingEl.checked?beatStatistics(heart.beats,false):statistics};
 return beatDisplayCache;
}
// Symmetric Gaussian filter with a 10 ms standard deviation and 20 ms radius.
// Time parameters are independent of the number of sample points.
function smoothBeatDisplay(beat){
 const dt=beat.intervalSeconds||0.01,pre=beat.preSeconds||0.25;
 const radius=Math.max(1,Math.round(0.02/dt)),weights=[];
 let weightSum=0;
 for(let k=-radius;k<=radius;k++){const weight=Math.exp(-0.5*(k*dt/0.01)**2);weights.push(weight);weightSum+=weight;}
 const result=beat.map((value,i)=>{
  if(!Number.isFinite(value))return null;
  const distance=Math.abs(i*dt-pre);
  const blend=distance<=0.040000001?0:Math.max(0,Math.min(1,(distance-0.04)/0.06));
  let sum=0,availableWeight=0;
  for(let k=-radius;k<=radius;k++){
   const neighbour=beat[Math.max(0,Math.min(beat.length-1,i+k))];
   if(Number.isFinite(neighbour)){sum+=(neighbour-value)*weights[k+radius];availableWeight+=weights[k+radius];}
  }
  return value+sum/availableWeight*blend;
 });
 result.clipped=beat.clipped;result.intervalSeconds=dt;result.preSeconds=pre;return result;
}
function drawBeatOverlay(){
 const plot=document.getElementById('beat-overlay'),context=plot.getContext('2d');
 const w=plot.clientWidth,h=plot.clientHeight,dpr=window.devicePixelRatio||1;
 if(!w || !h)return;
 const pixelWidth=Math.round(w*dpr),pixelHeight=Math.round(h*dpr);
 if(plot.width!==pixelWidth || plot.height!==pixelHeight){plot.width=pixelWidth;plot.height=pixelHeight;}
 context.setTransform(dpr,0,0,dpr,0,0);
 context.fillStyle='#fffafa';context.fillRect(0,0,w,h);
 const left=60,right=w-16,top=22,bottom=h-32,mid=(top+bottom)/2;
 const display=beatDisplayData(),displayedBeats=display.displayed,statistics=display.statistics,rawStatistics=display.raw;
 updateMeasurement(beatMeanEl.checked?statistics.mean:[]);
 const measuring=measureEl.checked&&measureState.available;
 measureState.geometry={left,right};
 let amplitude=0.1;
 for(let i=0;i<rawStatistics.mean.length;i++)amplitude=Math.max(amplitude,(Math.abs(rawStatistics.mean[i])+rawStatistics.sd[i])*1.15);
 for(const beat of heart.beats)for(const value of beat)amplitude=Math.max(amplitude,Math.abs(value)*1.15);
 context.font='12px system-ui';context.lineWidth=1;
 for(let i=-2;i<=2;i++){
  const y=mid-i*(bottom-top)/4;
  context.strokeStyle='#edc8cc';context.beginPath();context.moveTo(left,y);context.lineTo(right,y);context.stroke();
  context.fillStyle='#74464c';context.fillText((amplitude*i/2).toFixed(2),4,y+4);
 }
 for(let ms=-240;ms<=440;ms+=20){
  const x=left+(right-left)*(ms+250)/700;
  context.strokeStyle=ms%100===0?'#d89299':'#f0cdd0';
  context.lineWidth=ms%100===0?1:0.5;
  context.beginPath();context.moveTo(x,top);context.lineTo(x,bottom);context.stroke();
 }
 context.lineWidth=1;
 const xZero=left+(right-left)*0.25/0.7;
 context.strokeStyle='#bd8b91';context.beginPath();context.moveTo(xZero,top);context.lineTo(xZero,bottom);context.stroke();
 // Example sections: illustrative positions, not automatic measurements.
 if(beatReferenceEl.checked||measuring){
  const exampleX=t=>left+(right-left)*(t+0.25)/0.7;
  const m=measureState.marks.map(ms=>ms/1000);
  const sections=measuring?[[m[0],m[1],'P'],[m[1],m[2],'PR'],[m[2],m[3],'QRS'],[m[3],m[4],'ST'],[m[4],m[5],'T']]:[[-0.23,-0.13,'P'],[-0.13,-0.04,'PR'],[-0.04,0.04,'QRS'],[0.04,0.14,'ST'],[0.14,0.38,'T']];
  context.font='10px system-ui';context.textAlign='center';
  sections.forEach(([from,to,label],i)=>{
   const x=exampleX(from),end=exampleX(to);
   context.fillStyle=i%2?'rgba(90,115,145,0.035)':'rgba(90,115,145,0.075)';context.fillRect(x,top,end-x,bottom-top);
   if(end-x>=24){context.fillStyle='#667a91';context.fillText(label,(x+end)/2,top+11);}
  });
  context.textAlign='left';context.strokeStyle='rgba(75,102,145,0.5)';context.lineWidth=2.4;context.beginPath();
  if(beatReferenceEl.checked)for(let i=0;i<=350;i++){
   const t=-0.25+i*0.002;
   const g=(center,width)=>Math.exp(-0.5*((t-center)/width)**2);
   const example=0.13*g(-0.18,0.022)-0.15*g(-0.025,0.008)+g(0,0.009)-0.24*g(0.025,0.01)+0.28*g(0.25,0.05);
   const x=exampleX(t),y=mid-example*(bottom-top)*0.35;
   if(i)context.lineTo(x,y);else context.moveTo(x,y);
  }
  context.stroke();
 }
 const sampleX=(i,wave=displayedBeats[0])=>left+(right-left)*(i*(wave.intervalSeconds||0.01)-(wave.preSeconds||0.25)+0.25)/0.7;
 context.save();context.beginPath();context.rect(left,top,right-left,bottom-top);context.clip();
 const trace=(wave,color,width)=>{
  context.strokeStyle=color;context.lineWidth=width;context.beginPath();let started=false;
  wave.forEach((value,i)=>{
   if(!Number.isFinite(value)){started=false;return;}
   const x=sampleX(i,wave),y=mid-value/amplitude*(bottom-top)/2;
   if(started)context.lineTo(x,y);else{context.moveTo(x,y);started=true;}
  });context.stroke();
  context.strokeStyle='rgba(0,0,0,0.9)';context.beginPath();
  for(const [a,b] of timingBridgeSegments(wave,wave.map(value=>!Number.isFinite(value)),wave.intervalSeconds||0.01)){
   context.moveTo(sampleX(a,wave),mid-wave[a]/amplitude*(bottom-top)/2);
   context.lineTo(sampleX(b,wave),mid-wave[b]/amplitude*(bottom-top)/2);
  }
  context.stroke();
 };
 const validCount=heart.beats.length;
 if(validCount>1 && beatMeanEl.checked){
  context.fillStyle='rgba(15,130,112,0.14)';context.beginPath();
  const point=(i,value)=>[sampleX(i),mid-value/amplitude*(bottom-top)/2];
  for(let start=0;start<statistics.mean.length;){
   if(!Number.isFinite(statistics.mean[start])){start++;continue;}
   let end=start;while(end+1<statistics.mean.length&&Number.isFinite(statistics.mean[end+1]))end++;
   context.beginPath();
   for(let i=start;i<=end;i++){const [x,y]=point(i,statistics.mean[i]+statistics.sd[i]);if(i===start)context.moveTo(x,y);else context.lineTo(x,y);}
   for(let i=end;i>=start;i--){const [x,y]=point(i,statistics.mean[i]-statistics.sd[i]);context.lineTo(x,y);}
   context.closePath();context.fill();start=end+1;
  }
 }
 for(const beat of displayedBeats){
  context.setLineDash([4,3]);
  trace(beat,'rgba(15,130,112,0.2)',1);
 }
 context.setLineDash([]);
 if(validCount && beatMeanEl.checked)trace(statistics.mean,'#172f39',2.2);
 if(validCount && beatMedianEl.checked)trace(statistics.median,'#8053a6',2.2);
 if(measuring){
  const names=['P₁','P₂','Q₁','Q₂','T₁','T₂'];
  context.strokeStyle='#8053a6';context.fillStyle='#8053a6';context.lineWidth=1;context.font='11px system-ui';context.textAlign='center';
  measureState.marks.forEach((ms,i)=>{
   const x=left+(right-left)*(ms+250)/700;
   context.setLineDash([3,3]);context.beginPath();context.moveTo(x,top+24);context.lineTo(x,bottom);context.stroke();context.setLineDash([]);
   context.beginPath();context.moveTo(x-5,top+14);context.lineTo(x+5,top+14);context.lineTo(x,top+22);context.closePath();context.fill();
   context.fillText(names[i],x,top+10);
  });
 }
 context.restore();
 context.fillStyle='#74464c';context.textAlign='center';
 const labelEvery=(right-left)<500?200:100;
 for(let ms=-200;ms<=400;ms+=100){
  if(ms%labelEvery!==0)continue;
  context.fillText(String(ms),left+(right-left)*(ms+250)/700,h-10);
 }
 context.textAlign='left';context.fillText('mV ≈',4,14);
 context.textAlign='right';context.fillText('ms',right,h-10);context.textAlign='left';
 document.getElementById('overlay-note').textContent=heart.beats.length?
  t('overlayCount',{beats:heart.beats.length,valid:validCount,total:heart.totalBeats})+(beatSmoothingEl.checked?t('smoothed'):'')+t('overlayScale'):
  t('overlayWait');
}
document.getElementById('clear-beats').addEventListener('click',()=>{
 heart.beats=[];heart.totalBeats=0;heart.lastPeak=live.next-1;drawBeatOverlay();
});

const transport={session:null,after:null};
function decodeSamplePacket(buffer){
 const view=new DataView(buffer);
 if(view.byteLength<32 || view.getUint32(0,true)!==0x32534d48)throw new Error(t('invalidPacket'));
 const session=view.getUint32(4,true),first=view.getUint32(8,true),total=view.getUint32(12,true);
 const newest=view.getUint32(16,true),intervalUs=view.getUint32(20,true);
 const gain=view.getUint16(24,true),referenceMv=view.getUint16(26,true),count=view.getUint16(28,true),flags=view.getUint16(30,true);
 if(count>128 || view.byteLength!==32+count*2 || total-first!==count || newest<total || !intervalUs || !gain || flags>7)throw new Error(t('corruptPacket'));
 const words=Array.from({length:count},(_,i)=>view.getUint16(32+i*2,true));
 const leadOff=words.map(word=>word>>>14);
 const timingMissing=words.map(word=>word===0x3fff);
 const values=words.map(word=>(word>>>14)||(word&0x3fff)===0x3fff?null:word&0x3fff);
 return {session,first,total,newest,intervalUs,gain,referenceMv,unit:'mV-output',values,leadOff,timingMissing,leadStatus:flags>>>1,reset:!!(flags&1)};
}
const contactGuard={lowSamples:0,highSamples:0,timingSamples:0,ready:false,lastFault:0};
function resetContactGuard(){contactGuard.lowSamples=0;contactGuard.highSamples=0;contactGuard.timingSamples=0;contactGuard.ready=false;contactGuard.lastFault=0;}
function stabilizeContact(data){
 const required=Math.max(1,Math.ceil(1000000/data.intervalUs));
 data.values=data.values.map((value,i)=>{
  const rawStatus=data.leadOff[i];
  if(!Number.isFinite(value) && !rawStatus){
   contactGuard.highSamples=0;
   const timingOnly=data.timingMissing&&data.timingMissing[i];
   contactGuard.timingSamples=timingOnly?contactGuard.timingSamples+1:0;
   // Missed timer events are not measured electrode faults.
   // Do not count short gaps, but retain accumulated LOW measurements.
   if(!contactGuard.ready && (!timingOnly || contactGuard.timingSamples>timingGapLimits(data.intervalUs/1e6).maxSamples))contactGuard.lowSamples=0;
   return null;
  }
  contactGuard.timingSamples=0;
  if(rawStatus){
   contactGuard.lowSamples=0;
   contactGuard.highSamples=Math.min(required,contactGuard.highSamples+1);
   // Brief HIGH pulses invalidate only the affected values.
   // Block an already running display only after one second.
   if(contactGuard.highSamples>=required){contactGuard.ready=false;contactGuard.lastFault=rawStatus;}
   return null;
  }
  contactGuard.highSamples=0;
  if(!contactGuard.ready){
   contactGuard.lowSamples=Math.min(required,contactGuard.lowSamples+1);
   contactGuard.ready=contactGuard.lowSamples>=required;
  }
  if(contactGuard.ready)contactGuard.lastFault=0;
  return contactGuard.ready?value:null;
 });
 // Do not count header levels as additional measurement time, including empty packets.
 data.contactReady=contactGuard.ready;
 data.contactFault=contactGuard.lastFault;
}
let lastContactData=null,networkFailed=false;
function showContactStatus(data){
 lastContactData=data;
 const status=document.getElementById('contact-status');
 if(!data.newest){status.textContent=t('s9');document.getElementById('lead-yellow').textContent=t('s16');return;}
 const minus=!!(data.leadStatus&1),plus=!!(data.leadStatus&2);
 // Display the derived rule; this is not an additional measured electrode status.
 document.getElementById('lead-yellow').textContent=t('yellow')+(!minus||!plus?t('connected'):t('disconnected'))+t('derived');
 document.getElementById('lead-minus').textContent=t('red')+(minus?t('disconnected'):t('connected'));
 document.getElementById('lead-plus').textContent=t('green')+(plus?t('disconnected'):t('connected'));
 const fault=data.contactFault===undefined?(minus||plus):!!data.contactFault;
 status.textContent=fault?t('fault'):data.contactReady===false?t('checking'):t('contactOk');
 status.style.color=fault||data.contactReady===false?'#ffb86b':'#52e3b1';
}
function acceptSamplePacket(data){
 networkFailed=false;
 const discontinuity=transport.session!==null && (data.reset || data.session!==transport.session || data.first!==transport.after);
 if(discontinuity){
  saveSegment(true);archiveCursor=null;archiveInterval=null;
  archiveWarning='restart';
  live.values=[];live.cursor=null;
  resetHeartAnalysis(data.session!==transport.session);
 }
 if(data.gain!==measurement.gain || data.referenceMv!==measurement.referenceMv){saveSegment(true);resetHeartAnalysis(true);measurement={gain:data.gain,referenceMv:data.referenceMv};}
 if(discontinuity || transport.session===null)resetContactGuard();
 stabilizeContact(data);showContactStatus(data);
 baseline=data.referenceMv;
 collectArchive(data);collectLive(data);updateHeartAnalysis(data);
 transport.session=data.session;transport.after=data.total;
 if(!paused){latest=data;statusEl.textContent=t('live');}
}
async function poll(){
 const controller=new AbortController(),timer=setTimeout(()=>controller.abort(),3000);
 let delayMs=100;
 try{
  const query=transport.session===null?'':'?session='+transport.session+'&after='+transport.after;
  const response=await fetch('/api/samples.bin'+query,{cache:'no-store',signal:controller.signal});
  if(!response.ok)throw new Error('HTTP '+response.status);
  const data=decodeSamplePacket(await response.arrayBuffer());
  acceptSamplePacket(data);
  // Catch up in bounded packets; keep batching normal requests.
  if(data.total<data.newest)delayMs=0;
 }catch(error){networkFailed=true;if(!paused)statusEl.textContent=t('offline');document.getElementById('contact-status').textContent=t('staleContact');document.getElementById('lead-yellow').textContent=t('yellowUnknown');hideHeartRate('offlineRate');}
 finally{clearTimeout(timer);}
 setTimeout(poll,delayMs);
}
initializeLanguage();
poll();
requestAnimationFrame(animate);
</script>
</body></html>)HTML";

#undef HM_STRINGIFY
#undef HM_STRINGIFY_INNER
