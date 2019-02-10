# See It, Move It!

## Inspiration
Our first paradigm-shifting hackathon idea was SlapRat: in which we create a mouse that shakes itself periodically to keep a computer screen from falling asleep. While a titillating project concept at first, we quickly became disillusioned with SlapRat and wanted to create something more dynamic, more fun, that would bring people together. 

And, like a phoenix rising from the ashes of its own grave, the idea for BotBox emerged from the ashes of SlapRat. This would be a game where two friends would control two separate robots remotely around an arena and move objects to complete objectives. This was the idea that we worked toward for six grueling hours until we realized that one of the motors for our bots did not work, and that neither of us had the faintest idea on how to make a web server. After bashing our heads against the wall that is Flask, we decided that BotBox, while paradigm-shifting, was perhaps not the right wall to bash for Tartanhacks. 

Still desperately trying to submit something -- anything -- in time, we decided that since one of our robots did not work, we would simply have to create an equally fun, equally bringing-people-together, collaborative game with only one robot. 

It is our pleasure to introduce See It, Move It! A game that allows two people who are far apart to come together and interact in a remote area to do fun stuff and play with robots.

## What it does
The rules of the game are simple: the watcher observes the arena containing the robot and several blocks, and the mover who controls the robot can only listen to instructions from the watcher and is unable to see the arena (as well as the locations of the blocks, the robot, and the objective). The watcher must yell instructions at the mover, who has to respond to these instructions and together complete an objective of moving blocks into a designated area.

The robot communicates with the mover's remote through a radio-frequency (RF) transmitter and receiver. The mover and watcher communicate through any form of remote communication (phone call, Discord, video chat, etc.).

## How I built it
The robots were made with Arduino Nanos, control modules, and RF transceivers. They're powered by 4 AA batteries (6V). The control code is written with Robot Operating System (ROS). The blocks are made of cardboard and gorilla tape.

## Challenges I ran into
Many of the challenges we ran into were outlined in the first few paragraphs. It was extremely difficult for us to figure out how to use a Flask-backend web server to communicate with these robots, especially since neither of us has had experience with web server creation and design in the past. Although we tried very hard and worked on it for a long time, eventually we realized that under the time constraint, figuring out how to actualize our vision for BotBox was unrealistic.

Additionally, we were having hardware issues as one of the motors of one of the bots was not working, which meant that the bot had to be taken out of commission.

## Accomplishments that I'm proud of
We are proud that we attempted to learn how to use Flask and Ajax, since although we were unable to get our web server to do everything we wanted it to, we learned a lot and built a strong foundation for being able to actually do it in the future. We are also proud of being able to hack together a cute robot as quickly as we did, as well as being able to get the robot's RF receiver coded up and working in time.

## What I learned
We learned how to use Flask to make a web server, and attempted to use Ajax and Javascript for getting user input, as well as how to code on Arduino and using this to control a simple robot. 

## What's next for See It, Move It
While we feel that See It, Move It is a complete game on its own, we would love to be able to figure out how to evolve it into BotBox in the future. 
