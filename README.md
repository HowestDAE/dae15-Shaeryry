<a name="readme-top"></a>

<!-- GENERAL GAME INFO -->
<br />
<div align="center">

  <h2 align="center">Kirby's Adventure</h2>

  <p align="center">
    Kirby's Adventure is a platformer where you control Kirby as he navigates through different worlds, inhaling enemies to gain their abilities. Your objective is to defeat King Dedede and restore peace to Dream Land..
    <br />
    <strong>Original game : </strong>
    <a href="https://en.wikipedia.org/wiki/Kirby%27s_Adventure"><strong>General info »</strong></a>
    ·
    <a href="https://www.youtube.com/watch?v=3jt__MP4IzE"><strong>Youtube video »<strong></a>
    <br />
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#my-version">My version</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li><a href="#how-to-play">How To Play</a></li>
    <li><a href="#class-structure">Class structure</a></li>
    <li><a href="#checklist">Checklist</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

TODO: add screenshot 

Here's why:
TODO: describe why you chose this game 
    * I love Kirby :D
    * It seemed like the game would be challenging to make.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## My version

This section gives a clear and detailed overview of which parts of the original game I planned to make.

### The minimum I will most certainly develop:
* Most of, if not everything in, the first part of "Vegetable Valley"

### What I will probably make as well:
* .. 
* .. 

### What I plan to create if I have enough time left:
* .. 
* .. 

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started
Detailed instructions on how to run your game project are in this section.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* Visual Studio 2022

### How to run the project

Explain which project (version) must be run.
* any extra steps if required 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- HOW TO PLAY -->
## How to play

Use this space to show useful examples of how a game can be played. 
Additional screenshots and demos work well in this space. 
(WIP)

### Controls
* Arrow Keys - Movement
* Space - Jumping

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CLASS STRUCTURE -->
## Class structure 

### Object composition 
If you applied object composition (optional); explain where and how.

- AnimationController :
*It <b>HAS</b> and owns a bunch of Animation objects.

### Inheritance 
Explain where you applied inheritance (mandatory).

- Component Class : A lot of classes enherit from this class. This class serves as a quick way to create objects with "Transform" objects and "CollisionBody" objects. Examples are...
    * Animation
    * AnimationController
    * Camera
    * EnemySpawner
    * Entity
    * World

- Entity Class : This class encapsulates anything that is supposed to be considered alive in the game (Kirby, enemies...) Therefore it makes sense for the following classes to enherit from it.
    * Player
    * Enemy

- Enemy Class : This class groups up all enemies in the game. This serves as a base for every enemy and allows some enemies to share some stuff. Currently the enemies in the game are..
    * Waddle Doo

### ..

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CHECKLIST -->
## Checklist

- [x] Accept / set up github project
- [x] week 01 topics applied
    - [x] const keyword applied proactively (variables, functions,..)
    - [x] static keyword applied proactively (class variables, static functions,..)
    - [x] object composition (optional)
- [x] week 02 topics applied
- [x] week 03 topics applied
- [x] week 04 topics applied
- [x] week 05 topics applied
- [x] week 06 topics applied
- [ ] week 07 topics applied
- [ ] week 08 topics applied
- [ ] week 09 topics applied (optional)
- [ ] week 10 topics applied (optional)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Your Name - rity.simba-wina.kipula.tati@student.howest.be

Project Link: [https://github.com/HowestDAE/dae15-Shaeryry](https://github.com/HowestDAE/dae15-Shaeryry)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this space to list resources you find helpful and would like to give credit to. 

* [Example 1: cpp reference on std::vector](https://en.cppreference.com/w/cpp/container/vector)
* ..

<p align="right">(<a href="#readme-top">back to top</a>)</p>

