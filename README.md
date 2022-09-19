# Hex Editor Neo Structure Definition Library

This repository is an open database for binary structure definitions supported by [Hex Editor Neo](https://www.hhdsoftware.com/hex-editor) binary file editor for Windows (x86, x64 and ARM64).

## Introduction

Hex Editor Neo has a powerful component, called [Structure Viewer](https://hhdsoftwaredocs.online/hex/definitive-guide/structure-viewer/overview.html), which allows the user to parse contents of a binary file according to a specific *structure definition*.

![Structure Viewer](img/Structure-Viewer-collapsed%401.75.png)

A number of definitions are usually packed into one or more *structure definition files*. A structure definition file is written using built-in C-like language (see [Language Reference](https://hhdsoftwaredocs.online/hex/definitive-guide/structure-viewer/language-reference/overview.html)). [Kaitai Struct](https://doc.kaitai.io/) definition files are also supported by Hex Editor Neo.

## Structure Library

Starting from version 7.09, Hex Editor Neo is capable of automatically synchronizing a local Structure Library with this repository. Two synchronization levels are supported:

### **Release**

Hex Editor Neo synchronizes with latest repository release. This is the default synchronization level.

### **Head**
Hex Editor Neo always synchronizes with latest commit.

## Repository Structure

Structure definition files that are written using the built-in language are stored in the `h` subfolder, while `Kaitai Struct` files are stored in the `kaitai` subfolder.

[library.json](library.json) file lists all files that need to be added to the Structure Library. It also lists binding schemes and file path associations for each defined structure definition, if it is applicable.

Please note that not all files have to be listed in `library.json` file. If the file is `#include`-ed into another file, which is in turn added to the library, it does not have to be listed in the library file.

## Collaboration

Feel free to submit pull requests with corrections, new files and definitions to this repository.
