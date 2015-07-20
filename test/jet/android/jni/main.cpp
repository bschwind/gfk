#include <android_native_app_glue.h>
#include <GFK/System/Logger.hpp>
#include "AndroidJetGame.hpp"

/**
 * Our saved state data.
 */
struct saved_state
{
    int32_t x;
    int32_t y;
};

/**
 * Process the next input event.
 */
static int32_t handleInput(struct android_app* app, AInputEvent* event)
{
    // struct engine* engine = (struct engine*)app->userData;

    gfk::Logger::Log("Handling Input");

    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
    {
        // state.x = AMotionEvent_getX(event, 0);
        // state.y = AMotionEvent_getY(event, 0);
        return 1;
    }

    return 0;
}

/**
 * Process the next main command.
 */
static void handleCommand(struct android_app *app, int32_t command)
{
    jetGame::AndroidJetGame *game = (jetGame::AndroidJetGame*)app->userData;
    switch (command)
    {
        case APP_CMD_SAVE_STATE:
            gfk::Logger::Log("Save state");
            // The system has asked us to save our current state. Do so.
            // app->savedState = malloc(sizeof(struct saved_state));
            // *((struct saved_state*)app->savedState) = engine->state;
            // app->savedStateSize = sizeof(struct saved_state);
            break;
        case APP_CMD_INIT_WINDOW:
            gfk::Logger::Log("Init window");
            // The window is being shown, get it ready.
            if (app->window != NULL)
            {
                gfk::Logger::Logf("Screen size is (%i, %i)", ANativeWindow_getWidth(app->window), ANativeWindow_getHeight(app->window));
                game->ResizeWindow(ANativeWindow_getWidth(app->window), ANativeWindow_getHeight(app->window));
                game->InitializeGraphics();
            }

            break;
        case APP_CMD_TERM_WINDOW:
            gfk::Logger::Log("Terminate Window");
            // The window is being hidden or closed, clean it up.
            game->UninitializeGraphics();
            break;
        case APP_CMD_GAINED_FOCUS:
            gfk::Logger::Log("App Gained Focus");
            break;
        case APP_CMD_LOST_FOCUS:
            gfk::Logger::Log("App lost focus");
            // Also stop animating.
            break;
    }
}

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* app)
{
    gfk::Logger::Log("Start Main");
    jetGame::AndroidJetGame game(app);

    int lastScreenWidth = -1;
    int lastScreenHeight = -1;

    game.Initialize();

    int eventLoopTimeoutMs = 0;

    // Make sure glue isn't stripped.
    app_dummy();

    app->userData = &game;
    app->onAppCmd = handleCommand;
    app->onInputEvent = handleInput;

    if (app->savedState != NULL)
    {
        gfk::Logger::Log("Loading saved state");
        // We are starting with a previous saved state; restore from it.
        // state = *(struct saved_state*)app->savedState;
    }

    // loop waiting for stuff to do.
    while (true)
    {
        // Read all pending events.
        int eventID;
        int events;
        struct android_poll_source* source;

        // The first parameter is a timeout (ms).
        // 0 = Return without blocking
        // -1 = Block until an event is available
        eventID = ALooper_pollAll(eventLoopTimeoutMs, NULL, &events, (void**)&source);

        // Loop until all events are read, then continue
        // to draw the next frame of animation.
        while (eventID >= 0)
        {
            // Process this event.
            if (source != NULL)
            {
                source->process(app, source);
            }

            // Check if we are exiting.
            if (app->destroyRequested != 0)
            {
                game.UninitializeGraphics();
                gfk::Logger::Log("Stopping main");
                return;
            }

            eventID = ALooper_pollAll(eventLoopTimeoutMs, NULL, &events, (void**)&source);
        }

        if (app->window != NULL)
        {
            int newScreenWidth = ANativeWindow_getWidth(app->window);
            int newScreenHeight = ANativeWindow_getHeight(app->window);

            if (newScreenWidth != lastScreenWidth || newScreenHeight != lastScreenHeight)
            {
                game.ResizeWindow(newScreenWidth, newScreenHeight);
                lastScreenWidth = newScreenWidth;
                lastScreenHeight = newScreenHeight;
            }
        }

        // Done with events; draw next animation frame.
        // Drawing is throttled to the screen update rate, so there
        // is no need to do timing here.
        game.Tick();
    }
}
