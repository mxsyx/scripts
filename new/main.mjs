import fs from 'fs'
import exec from 'child_process'
import { Requests } from './requests.mjs'


class WalkFire {
  constructor() {
    this.requests = new Requests();
    this.url = "https://cdn2.00hzyzbf.com/ppvod/69F13640710BC1CA6CE6E7112AF9DFB0.m3u8";
    this.baseUrl = this.url.replace('index.m3u8','');
    this.rgxStr = {
      'ts': '.*\.ts',
      'm3u8': '.*\.m3u8'
    }
  }

  getCmdParams() {
    process.argv.indexOf('--url')
    console.log(process.argv)
  }

  start() {
    console.log(this.url)
    this.requests.get(this.url).then((content) => {
      const infUrl = this.isStreamInf(content, this.rgxStr['m3u8']);
      if (infUrl) {
        this.url = "";
        this.baseUrl = this.url.replace('index.m3u8','');
        this.start();
      } else {
        const tsUrls = this.getTsUrls(content, this.rgxStr['ts']);
        fs.writeFile('output.txt', tsUrls.join('\n'), (err) => {});
    //    this.download('output.txt')
      }
    });
  }

  download(fileName) {
    exec.exec(`aria2c -x 5 -i ${fileName}`, (err, stdout, stderr) => {
      if(err) {
        console.error(err);
        return ;
      }
      console.log(`stdout: ${stdout}`);
      console.log(`stderr: ${stderr}`);
    });
  }


  /**
   * 判断是否为备份源
   * @param {string} content HTTP响应内容
   * @returns 是备份源返回true,否则返回false
   */
  isStreamInf(content, rgxStr) {
    const matchResult = content.match(rgxStr);
    return matchResult ? matchResult[0] : false;
  }

  getTsUrls(content, rgxStr) {
    const tsUrls = [];
    const rgxIterator = content.matchAll(rgxStr);
    let rgxValue = null;
    while(true) {
      rgxValue = rgxIterator.next();
      if (rgxValue.done) break;
      tsUrls.push(`${this.baseUrl}${rgxValue.value[0]}`);
    }
    return tsUrls;
  }
}


const wf = new WalkFire();
wf.start();
