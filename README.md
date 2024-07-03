# node-api-examples

Did you wake up in the morning thinking what a blessing would be to be able to expose your C/C++ libraries to Node.js
and the JavaScript world? Is your thirst for learning so big you just want to know more about how to use the Node API if you ever need it in the future? 
Then, this might be the place where you can get started!

> ### Disclaimers
> This repo focuses on use cases you might run into when calling JavaScript from within your C/C++ code. <br/><br/>This repo assumes you are developing C/C++ code intendeed to be used from Node.js/JavaScript. This means you will always have a Node.js runtime enviroment in your disposal. Examples presented here might not be for you if your plan is to use your Node.js modules in your C/C++ project.<br/><br/>Examples in this repo demonstrate some of the basic things you can do with the (C) Node API, so they are small and simple. Production code will require more structure and complexity.

## Getting Started
* [Prerequisites](#prerequisites)
* [Tools](#tools)
* [How to run the examples](#how-to-run-the-examples)
* [Useful resources](#useful-resources)

### Prerequisites

<details>
<summary> C/C++ and JavaScript </summary>


The Node-API is an API that gives you access to JavaScript through C. You will most likely want to
use it to expose functionality of your existing C/C++ project to JavaScript, use some preexisting
C/C++ library in your project or just customize certain parts of your JavaScript code with the hope
to enhance their performance using C/C++.

In any case, this assumes some level of familiarity with JavaScript and/or C/C++. It is recommended 
you try to understand what you are trying to achieve and how much of C/C++ or JavaScript you need to
know before getting into the details of this repo.

Finally, this repo is specifically designed to show you examples of using the Node API C functions.
However, there is a higher level C++ API that you can find here: [node-addon-api](https://www.npmjs.com/package/node-addon-api). 
This might be easier to work with if you don't plan for maximum customization.

</details>


<details>
<summary> Command line tools </summary>


It is highly suggested you have some familiarity with the command line tool of your environment.
One way or the other, even when using an IDE, you will most likely have to do some things in the
command line.

</details>


### Tools

<details>
<summary> Node.js </summary>


Well, if you are trying to learn about the Node-API you might have guessed Node.js will be somewhat
necessary. Node.js is an engine that allows you to run JavaScript on a computer (outside of a browser).
To install it you can visit the [Node.js download page](https://nodejs.org/en/download/package-manager). 

The LTS version is the most stable latest version available and couple of versions prior to that are 
still maintainable. Anything older might be still fine depending on the features of the Node-API you 
want to use, however the latest version will give you a more enhanced developer experience. 
Note that Node-API was first supported in Node v8.0.0 so this is the oldest you can get. For more
information on which versions support Node-API you can have a look at the [Node-API Version Matrix](https://nodejs.org/api/n-api.html#node-api-version-matrix)

Finally, Node installation comes automatically with npm which we will be talking about next.
</details>



<details>
<summary> npm </summary>


npm, the “Node Package Manager”, is a set of tools for creating, maintaining, and sharing JavaScript 
modules (libraries). (Although not the only available package manager) It will be the primary tool
you use to install and use other peoples modules, as well as create and publish your own module. It
has functionalities for creating, building, testing your projects etc that can be customized to your
specific needs. You can read more about it in the [npm Docs](https://docs.npmjs.com/). 

</details>



<details>
<summary> C/C++ and Python </summary>


Besides Node and npm, you’ll need a set of C and C++ development tools and Python.

TODO

</details>


<details>
<summary> node-gyp </summary>


TODO

</details>


<details>
<summary> Other tools </summary>


* A **shell program**: This typically comes pre-installed on macOS and Linux. For Windows, you may want to consider PowerShell or cmd.
* An **IDE**: Visual Studio Code,  WebStorm and Visual Studio are all valid choices. You can choose the one for you. I personally use Visual Studio Code and occasionally Visual Studio for its debugging environment.

</details>

### How to run the examples

#### Build

First make sure you are in the folder of the example of your choice

```
cd <path to node-api-examples>/HowTo/<example>
```

Once there you can use the npm install command on your terminal to build the example

```
npm install 
```

Running this will create a build folder under the example's directory and at the end of the build 
it will copy the produced .node file under bin.

#### Run

To run the example you can simply run on your terminal:

```
npm test
```

or

```
node test.js
```

#### Experiment

The README.md in the example's folder should have enough information to give you some context of
what is going on in the code. Examples are bite size and full of comments, so feel free to jump
right into the code. Although examples are simple they might have extra code or suggestions for you
to experiment. You can alter the C/C++ code under the src/ folder of the example and the JavaScript 
code described in test.js. If you are changing code in src/ don't forget to rebuild the example!

> #### Note 
> For the sake of your sanity the addon generated for each example will have the the name example< number >. This way you don't run the risk of confusing the examples installed if you ever wish to install them at a random directory. (There is no real need for you to install them somewhere since they are not actually useful as modules, but you might just be a very interesting person. )


### Useful resources

* [The N-API documentation](https://nodejs.org/api/n-api.html)
* [node-addon-api on Github](https://github.com/nodejs/node-addon-api)
* [The Node-API Resource](https://nodejs.github.io/node-addon-examples/)
* [npm docs](https://docs.npmjs.com)
* [npm operations life-cycle](https://docs.npmjs.com/cli/v10/using-npm/scripts#life-cycle-operation-order)
* [node-gyp](https://github.com/nodejs/node-gyp) and [GYP documentation](https://gyp.gsrc.io/docs/UserDocumentation.md)

