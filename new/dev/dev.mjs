import commander from 'commander/index.js';

commander
 .option('-u, --url', '视频链接')
 .option('-o, --output', '保存的文件名')
 .option('-t, --threads', 'flavour of pizza');



commander.parse(process.argv);


const Aria2 = require("aria2");

const aria2 = new Aria2(options);

aria2.open().then(() => console.log("open")).catch(err => console.log("error", err));

 const magnet =
    "magnet:?xt=urn:btih:88594AAACBDE40EF3E2510C47374EC0AA396C08E&dn=bbb_sunflower_1080p_30fps_normal.mp4&tr=udp%3a%2f%2ftracker.openbittorrent.com%3a80%2fannounce&tr=udp%3a%2f%2ftracker.publicbt.com%3a80%2fannounce&ws=http%3a%2f%2fdistribution.bbb3d.renderfarming.net%2fvideo%2fmp4%2fbbb_sunflower_1080p_30fps_normal.mp4";
  
aria2.call("addUri", [magnet], { dir: "/tmp" });