# Congratulations Brett and Audrey for figuring it out!

![alt text](../master/Misc./Open.jpg "You did it!!!")


I'm really glad it worked! It worked fine when I was testing it but I was just a little worried since it's been going for a few months.

## Changing the Secret Location

To change where the geocache opens, look on lines 13-15 of [cache.cpp](../master/cache.cpp). You can replace the secret location latitude (`secLat`) and longitude (`secLon`) with the latitude and logitude of where you want it to open. I used Google maps to figure this out. Place a pin where you want it to open, and Google will give you the coordinates for it. You should be able to plug those directly into the secret location of [cache.cpp](../master/cache.cpp).


## Reseting the Counter
Before resetting the chache with a different location, you need to set `previous_ticks` on line 29 of [Project_BA1.ino](../master/Project_BA.ino) to whatever number the counter reads from the previous geocache. The geocache will then reset the counter back to 0 on the first start-up.
