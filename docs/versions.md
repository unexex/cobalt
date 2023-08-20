# Versions:

***
# Compilers and Interpreters:
## 23
### cobalt 
> **Type:** (Interpreter and Bytecoder) 

> **Binaries:** `cobalt` `cobaltc`

Original lightweight Cobalt interpreter and bytecoder. It can be compiled using
`make` and is the default option, it has the most and newest features and is
the most stable and portable. On sync with cobaltjit.
### cobaltjit 
> **Type:** (Optional JIT Compiler) 

> **Binary:** `cobaltjit`

Optional tool used for JIT compilation. It can be compiled using
`make jit` command. 

## 24
### cobalt24
> **Type:** (Beta Interpreter and Bytecoder)
> **Binary:** `cobalt` `cobaltc`

cobalt24, only given to testers and developers. [beta page](https://cobaltlang.vercel.app/beta)

### cobaltjit
> **Type:** (Optional JIT Compiler)
> **Binary:** `cobaltjit`

cobalt24 JIT, only given to testers and developers. [beta page](https://cobaltlang.vercel.app/beta)
***
# Other:
### cobalt-one
> **Type:** (Optional Standalone executable compiler)
> **Binary:** `cobalt-one`

cobalt24 standalone executable compiler. `make one`
### cobaltpre
> **Type:** (Optional Preprocessor)

> **Binary:** `cobaltpre`

Preprocessor for cobalt, it can be compiled using `make pre` command. It is
optional and uses the `preprocess` cobalt library but as a CLI tool. It is
written in cobalt.
## lua-cobalt 
> **Type:** (Optional Lua to Cobalt transpiler) 

> **Binary:** `lua-cobalt`

Optional tool used to convert Lua code to Cobalt code. It can be compiled using
`make lua-cobalt` command.
## minicobalt 
> **Type:** (Minimized one script interpreter ) 

> **Binary:** `minicobalt`

> **File:** `jit/minicobalt`

Lightweight ~4k lines version of cobalt, Included with `cobaltjit`, installed with
`make setup` after `make jit` is ran. Documentation is not provided and 
it is not recommended to use it because of its lack of features and stability.

***

<sub>Read credits [here](https://github.com/cobalt-lang/cobalt/blob/master/COPYRIGHTS.md)</sub>