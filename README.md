# Systems

## Animation System part 1
Dynamic head replacement, and other mesh exchange animation related to the looting and pick ups.

## Inventory System and UI
Player inventory UI and other related UI

1. Head tab. Contains all heads
2. Food tab. Contains all consumable food
3. Resource tab. Contains resource to make head, and cook food.

It might be possible to merge Food and Resource tab?


### Implementation
Each *Pickup* has a *Tags* field, some item can be in multiple categories. For example, a food can be a crafting resource.
Use single array to store all the items. The items are dynamically categorized and displayed using its *Tags* field. 

#### Slate and UMG
UMG is based on Slate.

##### Idea 1
The basic idea is having:

* InventoryWidgetBP, an UMG widget blueprint
* InventorySlotWidgetBP, an UMG widget blueprint

`InventoryWidget` handles layout and scrolling. `InventorySlotWidget` handles image loading, might be able to bind help message tooltip here?

It is ideal to handle all the logic in the blueprint, without any base C++ class.

##### Idea 2
Slate version of scrollable pane is ideal. Also the slot can be turned into a slate class as well. So we just need a single UMG `UInventoryWidget` wraps both `SScrollPane` and `SSlot`. The user interaction will then be able to handled in UMG.  

## Spawn System
Pickup spawn, NPC spawn. 

## Loot System part 1
Naive loot system, can be just hard coded



## Craft System



## User Input System
Queue the user inputs, trigger appropriate actions

## Animation System part 2
Animation related to fighting pose.

## Fighting Collision System
Collision and damage design and calculation.




## NPC AI System
Game AI development

## Level Design, NPC Design
Game level design, enviroment creations.

## Loot System part 2
Advance loot system, with proper random output.





## Game Music