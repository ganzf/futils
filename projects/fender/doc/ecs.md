# ECS


If you want to know more about systems, [follow this link](systems.md)

**Also its recommended you [read this](./Fender.md) before going further into details**

## [Entities](./entities.md)

+ [GameObject](./entities/GameObject.md)
  + Transform
  + Outline


+ [Window](./entities/Window.md)
  + Meta
  + Transform
  + Color
+ Camera
  + Transform
  + Camera
+ Grid : GameObject
  + Grid
+ Text : GameObject
  + Text
  + Color
+ Sprite : GameObject
  + Image
  + Color
  + Texture
+ Bar : GameObject
  + Color
  + Text
  + Progressive
  + Texture
+ Button : GameObject
  + Color
  + Image
  + Text
  + Clickable
  + Hoverable
+ TextBox
  + Transform
  + Text
  + Color
  + Scrollable
+ Sound
  + Audio
+ Music
  + Audio
+ Cursor
  + Transform
  + Color
  + Image
  + Effect
+ Popup (with multiple choices)
  + Transform
  + Color
  + Text
+ Container
  + Transform
  + Image
  + Color
  + Content
+ InputField
  + Transform
  + Image
  + Color
  + Text
+ Slider
  + Transform
  + Image
  + Color
  + Clickable

## [Components](./components.md)

+ [Meta](./components/Meta.md)
  + name
  + style
+ Transform
  + position
  + scale
  + rotation
  + isRelative
+ Color
  + color


+ Text
  + content (string)
  + font
  + font-size
  + modifiers (bold, underlined, italic...)
+ Image
  + filepath (string)
  + layer, z-index
+ Progressive
  + min
  + max
  + current
  + callback ?
+ Texture
  + filepath (string)
+ Clickable
  + function
+ Hoverable
  + function
+ Scrollable
  + min
  + max
  + currentScroll
  + autoScroll (bool)
+ Effect
  + ​
+ Audio
  + filepath (string)
  + loop (bool)
  + volume 
+ Content
  + text (string)
  + max
  + possible values (only numbers ? )
  + masked (for passwords)
+ Camera
  + Background (color)
  + Field of view (float)
  + PostProcessing effects (antialiasing, etc...)

## [Systems](./systems.md)

### 
