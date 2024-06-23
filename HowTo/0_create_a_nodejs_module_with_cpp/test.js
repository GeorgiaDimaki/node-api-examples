const example = require('.') // will require the folder test.js is in.
// since the folder has a package.json we can load the "example" module without installing it.

console.log(example) // should print {} since we have not added any functionality yet.