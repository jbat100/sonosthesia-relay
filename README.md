# Sonosthesia-Relay

Part of the [Sonosthesia](http://www.sonosthesia.com/home) project.

An audio plugin based on the [JUCE toolkit](https://www.juce.com/features) which allows the product to be compatible with a number of standards, most significantly VST and AU. Pre-compiled binaries will be provided soon but you can tweak the JUCE project to your needs if they are not sufficient (and feel free to contribute...).

## Project Overview

This project extends the functionality of the [Sonosthesia-Analyser](https://github.com/jbat100/sonosthesia-analyser/tree/develop) to MIDI and automation data. It allows this musical control data to be assigned to control groups and descriptors and routed to multiple OSC targets (host/port combinations). 


It also allows MIDI notes to be exposed as **dynamic output channels** and automation data to be exposed as **static output channels** to the [Sonosthsia-Hub](https://github.com/jbat100/sonosthesia-hub/tree/develop) (see [Sonosthesia Protocol](http://www.sonosthesia.com/protocols)). 


