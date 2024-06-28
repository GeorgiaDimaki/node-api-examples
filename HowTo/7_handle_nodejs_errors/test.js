const { main } = require('.') // will require the folder test.js is in.
// since the folder has a package.json we can load the "example" module without installing it.

// Since main is a named export we can use the above syntax to load it.

// let's call main with different type of arguments

main(5)         // this should not create an error

try {
    main('5')   // however this will ...
} catch (e) {
    console.log(e)
}


try {
    main()      // and this one will ...
} catch (e) {
    console.log(e)
}