# GameSense™ Plugin for Unreal Engine 4
GameSense™ Plugin for UE4 simplifies the process of integrating GameSense™ in your project. It minimizes the amount of work required to communicate with the GameSense™ server through a simple-to-use C++ API with Blueprint bindings.

## More info
* [GameSense Developer Portal](https://steelseries.com/developer)
* [GameSense SDK documentation](https://github.com/SteelSeries/gamesense-sdk)
* [Unity Engine plugin](https://github.com/SteelSeries/unity-gamesense-client)

# Installation

To install from this repo, simply copy the contents of this directory to your project's `PROJECT_ROOT/Plugins/Runtime/SteelSeriesGameSense`. Next, regenerate your source code project. For instance, right-click on your `.uproject` file and select ***Generate Visual Studio project files***. Open your project and verify that the client appears among the project plugins: go to ***Edit > Plugins*** and look under category ***Other***. Also, open your project's main module's `.Build.cs` and add `"SteelSeriesGameSense"` to the public dependency module names. Rebuild your project.

The client plugin will also be available soon in the Unreal Engine Marketplace.

The client relies on the presence of the SteelSeries Engine (aka the GameSense™ server). You can download it from [here](https://steelseries.com/engine).

At this time, only Windows and macOS platforms are supported.

# Quick Start Guide
**NOTE**: It is strongly advised you familiarize yourself with how GameSense™ works first! Please make sure to visit the SDK pages (link at the top) to learn the high-level concepts.

The plugin exposes both C++ and Blueprints interfaces. Both have identical features and functionality and therefore it is valid to have a mixed usage of both. For a better experience, we recommend you first try the Blueprint visual scripting to interface with GameSense™, due to the process being somewhat guided thanks to the context sensitive node creation.

The GameSense™ workflow boils down to the following steps:

+ Starting the client
+ Registering your game
+ Registering (or binding) events (with handlers)
+ Sending event updates during gameplay
+ Stopping the client when gameplay is done

## Blueprints

**NOTE** The client plugin ships with a sample **Actor Blueprint** to serve as an example. You can locate it in the plugin's `Content` directory. To view it in the content browser, follow these steps:
1. Make sure the plugin content is visible.

![show-plugin-content](/Resources/show-plugin-content.png)

2. Choose a path in the content browser.

![gamesense-plugin-content](/Resources/gamesense-plugin-content.png)

3. You should now see a Blueprint named ***GameSense***.

In this guide, however, we will make an actor from scratch.
Create a new blueprint class, select **Actor** as a parent class and open the new class in the editor.

![blueprint-class-creation](/Resources/blueprint-class-creation.png)

### Registering a Game

Adhering to the process described above, we proceed with the first steps.

1. Open ***EventGraph*** and drag off the exec pin of ***Event BeginPlay*** to place a new node.
2. From the list, find category ***GameSense > Client*** and select ***Start***.

![blueprint-start](/Resources/blueprint-start.png)

**NOTE**: The vast majority of the nodes conerning us will be located under category ***GameSense***.

3. Drag off the exec pin of ***Start*** function and select ***Register Game***. Enter desired values for the function arguments.
You may create something that looks similar to the following.

![blueprint-register-game](/Resources/blueprint-register-game.png)

### Binding Events ###

1. Create a new function, name it ***bindMyEvent*** and open it in the editor.
2. Since this time we want to bind an event, let's create a node for function ***Bind Event***. Fill out the node with desired values. Make sure the game name matches what you specified in ***Register Game***. Stop at the last argument.
3. Drag off ***Handler Collection*** and select ***Make Handler Collection***. Notice the power of Blueprints: in this context ***Make Handler Collection*** is the only meaningful item and pretty much everything else gets filtered out from the list of actions.
4. Drag off ***Return Value*** pin of the newly created node and select ***Add Color Handler***. The new function executes in context of the newly created handler collection (note the ***Target*** pin).
5. Drag off ***Device-Zone***. Note that you are given an option of using the implicit make node ***Make SSGS_IlluminationDeviceZone***. Let's not use it and instead, select a device-zone action from ***GameSense*** category, ***Make Mouse Wheel*** for instance.

**Attention**: You should almost always prefer to select make nodes from under ***GameSense*** category. In many cases the default-constructed structures contain invalid data. The exception to this is when there is no action available under ***GameSense***.

6. Similarly for ***Color Specification***, create ***Make Gradient Color Effect***, and then use ***Make SSGS_RGB*** for each argument, ***Start Color*** and ***End Color***.
7. Connect the exec pins to ensure correct execution order: ***Bind MyEvent -> Make Handler Collection -> Add Color Event -> Bind Event***.
8. Drag off the exec pin of ***Bind Event***, create ***Send Event***, specify appropriate values for ***Game Name*** and ***Event Name***. Also, make structure for ***Data*** and specify a value of *100*. This will initialize the event on the zone on the device.

At this point, your graph should resemble the image below.

![blueprint-complete-event](/Resources/blueprint-complete-event.png)

Be sure to invoke ***bindMyEvent*** following ***Register Game*** as illustrated below.

![blueprint-bind-event](/Resources/blueprint-bind-event.png)

9. Compile and save the blueprint, then close the blueprint editor.
10. Drag the blueprint asset to the world outliner and click on **Play**. Your mouse wheel should be illuminated with green color.

### Sending Event Updates ###

In the previous step we already send a single event update to initialize the zone on the mouse. You can hook up to any event event in any blueprint to send updates to the server. One decent idea is to use the event we just defined to reflect the player's health. To do so, edit your character's blueprint and create a new function ***takeDamage***. Define it as below.

![blueprint-take-damage](/Resources/blueprint-take-damage.png)

In this function, the ***Health*** value will be decremented with each invocation and reset to *100* once it hits *0*. The value will also be sent to the GameSense™ server with ***Send Event***. If your character has a collision component, you could call ***takeDamage*** from event ***OnComponentHit***. Also, make sure the collision component is set to generate ***Hit*** events. Alternatively, you could use events such as ***BeginOverlap***.

![blueprint-component-hit](/Resources/blueprint-component-hit.png)

**!!! ATTENTION !!!** Do not forget to stop the client to release its resources when it is no longer needed. A good place to do so is in the **Actor's** ***EndPlay*** event. In this case, the client will be stopped once your blueprint **Actor** gets removed from the game world.

![blueprint-gamesense-stop](/Resources/blueprint-gamesense-stop.png)

## C++

Remember that you have an option to use the client entirely through code, entirely through bluerprints, or have a mix of non-redundant calls from both. In this section we will create an equvalent sequence of calls to the one above in an **Actor** C++ class.

```
#include "SSGS_Client.h"

...

void AGameSense::BeginPlay()
{
    AActor::BeginPlay();

    ssgs::Start();
    ssgs::RegisterGame( { GAME_NAME, "My Fancy Game" } );

    USSGS_ColorEffectSpecification* pCesg =
        USSGS_ColorEffectSpecificationGradient::MakeGradientColorEffect( FSSGS_RGB{ 255, 0, 0 },
                                                                         FSSGS_RGB{ 0, 255, 0 } );

    USSGS_HandlerCollection* pHc = USSGS_HandlerCollection::MakeHandlerCollection();
    pHc->AddColorHandler( USSGS_IlluminationDeviceZoneFactory::make_mouse_wheel(),
                          ESSGS_IlluminationMode::Percent,
                          pCesg );

    ssgs::BindEvent( { GAME_NAME,
                       "HEALTH",
                       0,
                       100,
                       ESSGS_EventIconId::Health,
                       pHc } );

    ssgs::SendEvent( { GAME_NAME,
                       "HEALTH",
                       FSSGS_EventData{ 100 } } );
}

void AGameSense::EndPlay( const EEndPlayReason::Type EndPlayReason )
{
    AActor::EndPlay( EndPlayReason );
    ssgs::Stop();
}
```

Then, somewhere else in your game code, you can send event updates with the following:

```
ssgs::SendEvent( { GAME_NAME,
                   "HEALTH",
                   FSSGS_EventData{ _mHealth } } );
```

### Tips ###
+ Do not attempt to instantiate **UObject**-derived GameSense objects by yourself. Each **UObject**-derived GameSense class has a static method, usually called `Make*()`, to carry out the task. Use those methods instead.

# Preparing Image Data
GameSense for OLED/LCD allows you specify bitmaps as sources for frame data. This section details the options available to you to accomplish this.

## Texture Assets
It is more than likely that freshly imported texture assets will not work out of the box with GameSense for OLED/LCD. To ensure the client is able to process the assets, follow these steps:

1. In content browser, navigate to the directory containing your texture assets and select those that you'd like to use.
2. Right-click on any of the selected assets and navigate to ***Asset Actions > Bulk Edit via Property Matrix...***
3. In the new window, locate and set the following properties to the corresponding values:
   + Mip Gen Settings = _NoMipmaps_
   + Compression Settings = _VectorDisplacementmap (RGBA8)_
   +  sRGB = unchecked
4. Go to ***File > Save All...***
5. Close the window.

The texture assets now have the correct format and can be used as image sources for frames data in screen handlers. Simply use `USSGS_ImageDataTexture2D::MakeImageDataFromTexture(UTexture2D*)` from C++ or `MakeImageDataFromTexture()` from Blueprints. You still need to ensure the textures have correct size for the target screen device.

## Bit Vector
You can supply an byte array where the value of each bit corresponds to a white or black point on the screen as described [here](https://github.com/SteelSeries/gamesense-sdk/blob/master/doc/api/json-handlers-screen.md#showing-raw-bitmaps). It is mandatory for the length of the array to be equal to `ceiling(`_`width`_ `*` _`height`_ `/ 8)`, where _width_ and _height_ are the dimensions of the target screen device.

## Subclass of `USSGS_ImageDataSource`
You also have an option of making your own image source that suits your specific needs. To do it, create a class that derives from `USSGS_ImageDataSource` and reimplement `GetData()`. This function is expected to return the byte array as described above. The benefit of this method over the bit vector is that `GetData()` receives `FSSGS_ScreenDeviceZone` object which you can use to obtain target device width and height. Please refer to the implementation of `USSGS_ImageDataTexture2D::GetData()` for an example.

# General Advice
+ By default, the **SteelSeriesGameSense** module is loaded at the *PreDefault* stage. Please ensure it gets loaded before any modules that depend on it.
+ Please be mindful of the frequency of your `SendEvent()` calls. Ideally, you should only send events when the underlying event data has changed. Sending redundant data, or sending events every game frame, _may_ have unforeseen consequences.
+ You generally should consider sending initial values for each event before the game starts running regular updates.
+ Remember to bind your handlers for a particular event all at once. Any consecutive call to `BindEvent()` for the same event will override all previously bound handlers.
+ During development you can increase log verbosity for the  *SSGS_Client* category. You will see lots of helpful output along with the messages from the GameSense™ server which can help you debug your handlers.
+ In the event of a critical failure, such as when the client can't communicate with the GameSense™ server, the client assumes an inactive state, where all the API calls have no effect.
+ The event handlers you bind will be the defaults for your game. However, the end user can customize or disable the handler behavior in SteelSeries Engine.
+ This document is, by no means, meant to be a comprehensive GameSense™ guide. You should refer to [SteelSeries Developer Portal](http://developer.steelseries.com/gamesense) for more information.

# License
The GameSense™ Client for UE4 is a free, open-source project, available under the MIT license.
