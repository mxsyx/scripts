/**
 * 通用网络库
 */

import https from 'https'


class Requests {
  constructor() {
  }
  
  /**
   * GET请求
   * @param {string} url 请求地址
   */
  get(url) {
    return new Promise((resolve, reject) => {
      https.get(url, (res) => {
        // 响应内容
        let content = '';
        res.on("data", (data) => {
          content += data;
        });
        res.on("end",() => {
          resolve(content);
        });
      });
    });
  }
}

export { Requests };
