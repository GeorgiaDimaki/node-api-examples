const { main } = require('.') // will require the folder test.js is in.
// since the folder has a package.json we can load the "example" module without installing it.

// Since main is a named export we can use the above syntax to load it.


console.log(`The primitive value generated is ${main()}`) 