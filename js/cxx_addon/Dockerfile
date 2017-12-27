FROM node:latest

RUN npm install -g node-gyp
RUN mkdir /usr/src/cxx-addon/
ADD addon.cpp /usr/src/cxx-addon/addon.cpp
ADD binding.gyp /usr/src/cxx-addon/binding.gyp
ADD main.js /usr/src/cxx-addon/main.js
WORKDIR /usr/src/cxx-addon/

RUN node-gyp configure
RUN node-gyp build

CMD node main.js