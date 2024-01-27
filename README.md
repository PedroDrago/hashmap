# Hashmap

WORK IN PROGRESS

This is my implementation of a Hashmap in C. Thanks [Saiago](https://github.com/Grsaiago/hashmapC) for suggesting this little project. I've tried to use as few functions from stdlib as possible.

Disclaimer: I'm experimenting on C code style, I'm used to a style norm made by [42](https://42.fr/en/homepage/), but to discover what I like most I'm trying new stuff, for example, single line if statements.



### About hashmaps
Hashmap is a data structure extremely usefull and performant, for those who already know some Javascript `objects` are HashMaps. They are `key`:`value` structures, that means that you register a `value` attached to a `key` that represents it, so you can retrieve the `value` that corresponds to the `key`.

Hashmaps are very performant because they use `arrays` instead of a linked list, so the access does not require traversal, it is almost instant. This structure is called a **Hashmap** because it maps `key` to `value` using **hashes**. In this structure hashing means to take the given `key` (like `'Name'`), passing it in a Hashing Algorithm, and getting a unique (if we're using a good hashing technique) number that we'll be using as index for storing our data in the Hashmap array. So when we ask to get the value that corresponds to the `key`, the hashmap will hash this `key`, access the array in the hashed `key` position, and retrieve the `value` that is stored there.

A problem hashmaps have is what is called **Collision**: Collision is when two different `keys` generate the same hash. That is more common when a simpler hash algorithm is used (I guess when the hashmap array is small it can also increase the chance of collision, at least with my hashing technique). The solution I've used to is to initiate a linked list in the `key` that generated the collision, and when retreiving the Hashmap will start comparing the wanted `key` string to the `key` string stored in each Node of the list until it finds a match.
