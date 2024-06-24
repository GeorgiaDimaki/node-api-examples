const example = require('.') // will require the folder test.js is in.
// since the folder has a package.json we can load the "example" module without installing it.

console.log(example) // should print { main: [Function: main] }

console.log(`\nCalling the main function returns: ${example.main()}\n`) 
// the function does not return something yet. undefined will be printed


