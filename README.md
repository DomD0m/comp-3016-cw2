# comp-3016-cw2
 OPENGL COURSEWORK FOR COMP 3016
My signature for my work is placed in corner of the grass texture within the scene that is loaded.
How does this project work? we are using OpenGL to make a modelled scene with c++. The way the program is doing this, is by talking to all of its classes to be able to generate a matrcies from a GLTF file to be able to rebuild the model within the OPENGL window, this also allows to grab any texture when correctly name and be able to load this. This is done through GLTF files because of the main part of the model.ccp which has the traverse node, this traverse node is able to go through each section of the GLTF and write back the data that is needed for the OPENGL to recreate the model within it. These GLTF files can then be modified to place the models within different spaces across the window and other areas or can change the textures to have different textures on the models loaded in the space. To be able to move around within the space of the OPENGL window you are to use both your mouse and keyboard and the mouse can be used to rotate the camera whilst the WASD keys move the camera in those respectfully each of the keys cardinal directions (such as w going forward,s going down, a going left and d going right).To allow for the .exe to be able to run the file must contain all the models that are going to be loaded and the shaders and libaries and include for the project which should be in the folder already. So you should be able to just boot up the .exe from the minute u download it.
How does the program code work?:
I'll start by explaining each of the classes within the code:
VBO class: 
makes an id and then its the vertex buffer object this supplies the vertex data for the opengl and window to allow for model vertices be found and added to an object to store the info.
EBO class:
makes an id and then ebo is the an array of pointers that mark up the vertices to the indices to then print on to the window.
VAO class:
makes an id and links the attributes for all the parts of models or meshes.
Shader Class:
The shader class makes the shader program from using the .vert and .frag files to make up the shaders, and this makes up the model lighting and graphics.
texture class:
Grabs the texture image and then assigns it to the correct unit and wraps the texture on to the model, this is reading it with the Stb.
Mesh class:
sets up the variables to talk to the VAO and get the vertices and indices and textures for the model to create the mesh for it and whilst talking to the camera aswell.
Camera class:
the camera system sets up inputs for the user to be able to move around the scene and spectate it from different angles also makes where the POV for looking on to the scene is.
Model Class:
The model class is where the node traverse takes place and reads the gltf file and gets the full information to talk to everything else and produce the model file onto the screen.
The last part is the main:
where you load the file locations for the model and put it all into the window and tell opengl to open an window.

What did I start with:
Started with a basic understanding of c++ and knew what OpenGl was and it was used in games. From there I took to learn about OpenGL through sources but my level of knowledge of the subject was heavily limited. So for my project I decided to heavily stick to my pitch and make a little forest scene where you have several trees and a little mushroom cottage (these are blender models from Online), this was to add a small tabletopish vibe to the scene, my idea of building this came from a previous love of modeling figures and figure creation such as WarHammer and Gundam, as I sort to want to build a small forest environment in a fantasy setting or something you could encounter whilst in a Dungeons and dragons campaign so this was able to come from multiple hobbies or previous loves of different franchises to come up with what I wanted to make. I wanted everything to feel cozy and believe the additional lighting to the scene is able to give that aesthetic to the scene.
What did I want to add: Whilst coding this time was a massive limitation as my knowledge was heavily limited with OpenGl and groundwork must be done before I'm able to truly grasp what every moving piece is doing and what must be done to make results. So as stated in the pitch I wanted to make a mini particle system within OpenGl to replicate rain falling on to the forest but I unfortunately wasn't able to get around to this and instead all I was able to figure out was how to make a random number generator which would be the first part of making the particles fall from the sky.
Another additional piece that only came to me whilst coding was that Hard changing around the GLTF files matrices is annoying and I wanted to be able to do this within the OpenGL code itself but everything I did was clunky and not very good for the program run speed so I decided to scrap this idea and stay to changing the matrices, within the GLTF files.