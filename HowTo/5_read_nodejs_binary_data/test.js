const { main } = require('.') // will require the folder test.js is in.
// since the folder has a package.json we can load the "example" module without installing it.

// Since main is a named export we can use the above syntax to load it.

// let's call main with different type of arguments
const arraybuf = new ArrayBuffer(8)

main(Buffer.from('hello'))      // buffer
main(arraybuf)                  // array buffer 
main(new DataView(arraybuf))    // dataview
main(4)                         // should fail since 4 is not an object
main({})                        // should fail since {} does not represent binary data.

// Do you notice anything interesting?