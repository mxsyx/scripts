/*
 * File: /main.ts
 * Author: Mxsyx (mxsyxin@gmail.com)
 * Created At: 2020-12-06 04:38:35
 * ------
 * Last Modified: 2020-12-13 11:08:16
 * Modified By: Mxsyx (mxsyxin@gmail.com>)
 * ------
 * Lisense: MIT
 * H.264 Downloader
 * Exec: deno --allow-net --allow-write main.ts [urr]
 */

const THREADES_NUMBER = 10
const OUTPUT_DIR = Date.now()

if (OUTPUT_DIR) {
  Deno.mkdirSync(OUTPUT_DIR.toString())
}

const baseUrl = Deno.args[0].replace("index.m3u8", "1000k/hls")
let lock = false

interface TS { id: string, url: string }

const tses: TS[] = []
const concats: string[] = []

async function download(rid: number) {
  while (true) {
    const ts = tses.shift()
    if (!ts) {
      if (!lock) {
        const encoder = new TextEncoder()
        Deno.writeFileSync(`./${OUTPUT_DIR}/concat.txt`, encoder.encode(concats.sort().join('\n')))
        lock = true
      }
      return
    }
    console.log(`下载器: ${rid}  下载: ${ts.url}  剩余: ${tses.length}  `)
    const response = await fetch(ts.url)
    const arrayBuffer = await response.arrayBuffer()
    Deno.writeFileSync(`./${OUTPUT_DIR}/${ts.id}`, new Uint8Array(arrayBuffer))
    concats.push(`file '${ts.id}'`)
  }
}

fetch(`${baseUrl}/index.m3u8`)
  .then((response) => response.text())
  .then((content) => {
    for (let match of content.matchAll(/.*\.ts/g)) {
      tses.push({ id: match[0], url: `${baseUrl}/${match[0]}` })
    }

    const len = parseInt(String(tses.length / THREADES_NUMBER))
    for (let i = 0; i * len < tses.length; ++i) {
      download(i + 1)
    }
  })

export default {}
