const { main } = require('.') // will require the folder test.js is in.
// since the folder has a package.json we can load the "example" module without installing it.

// Since main is a named export we can use the above syntax to load it.

// try calling the function with various number of arguments.
// we are not concerned about the type of the arguments yet, so this shouldn't matter.
main('hello', 'world')
