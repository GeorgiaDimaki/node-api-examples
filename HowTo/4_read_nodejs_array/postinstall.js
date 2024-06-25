const fs = require('fs/promises')

const addon = "example.node"
fs.mkdir("bin").catch(() => {}).then(fs.copyFile(`./build/Release/${addon}`, `./bin/${addon}`)).catch(e => console.log(e))