#!/usr/bin/env node
// v2ray-switch

const net = require('net')
const https = require('https')
const fs = require('fs')
const { spawnSync } = require('child_process')

const CONFIG_PATH = '/usr/local/etc/v2ray/config.json'
const SUBSCRIPTION_URL = ''

let locked = false

function parseSubscription(data) {
  const buffer = Buffer.from(data, 'base64')
  const b64List = buffer.toString().replace(/vmess:\/\//g, '').split('\n').slice(0, -1)
  return b64List.map(b => JSON.parse(Buffer.from(b, 'base64').toString()))
}

function tcpPing(host, port) {
  const justNow = Date.now()
  const socket = new net.Socket()
  socket.setTimeout(5000)
  return new Promise((resolve, reject) => {
    socket.on('connect', () => {
      resolve(Date.now() - justNow)
      socket.destroy()
    }).on('error', e => {
      reject(e.message)
    }).on('timeout', () => {
      reject('timeout')
    }).connect(port, host)
  })
}

function main(data) {
  const vmessList = parseSubscription(data)
  vmessList.forEach(async vmess => {
    try {
      vmess['differ'] = await tcpPing(vmess['add'], vmess['port'])
      if (!locked) {
        console.log(vmess)
        const f = fs.readFileSync(CONFIG_PATH)
        const config = JSON.parse(f.toString())
        config['outbounds'][0]['settings']['vnext'][0]['address'] = vmess['add']
        config['outbounds'][0]['settings']['vnext'][0]['port'] = vmess['port']
        fs.writeFileSync(CONFIG_PATH, JSON.stringify(config))
        spawnSync('sudo service v2ray restart')
        locked = true
      } else {
        process.kill(process.pid, 'SIGTERM')
      }
    } catch (error) {
      console.log(`${vmess['add']}:${vmess['port']}  ${error}`)
    }
  })
}

// start
https
  .get(SUBSCRIPTION_URL, res => {
    let data = ''
    res.on('data', chunk => data += chunk)
    res.on('end', () => main(data))
    res.resume()
  })
  .on('error', e => {
    console.log(`Got error: ${e.message}`)
  })
