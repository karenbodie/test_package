# Test Package

A small sandbox for testing ROS things.

## Talker and Listener

Try using different nodehandle types in the code and see what connections look like with `rqt_graph`. Note: for disconnected topics, you should unhide leaf topics and sinks to view them in the graph.

```
roslaunch test_package talker_listener.launch
```

## Hello World

Here's a node with a publisher and a subscriber, which reads a parameter for the input topic. The publisher is triggered to publish in the subscriber's callback function. Try changing the launch file namespaces, and nodehandle types, and see if you can get the parameter to match without causing a shutdown.

```
roslaunch test_package hello_world.launch
```

## Callback Threads

Try running three callback threads synchronously and asynchronously:

```
roslaunch test_package callback_threads.launch
roslaunch test_package callback_threads.launch  use_async:=true
```