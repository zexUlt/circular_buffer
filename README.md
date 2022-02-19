# ciricular_buffer

This is yet another implementation of STL-styled fixed-size ring buffer. [Wiki](https://en.wikipedia.org/wiki/Circular_buffer)

# Enable tests
This project utilizes `Boost::unit_test_framework`. So, in order to enable it and test this container, you would need to execute following commands in terminal:

Ubuntu:
```bash
$ mkdir build
$ cd build
$ cmake -DENABLE_TESTING=1 ..
$ make
```
