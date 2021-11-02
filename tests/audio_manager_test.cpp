#include <catch2/catch.hpp>

#include "../src/chestnut/engine/init.hpp"
#include "../src/chestnut/engine/audio/audio_manager.hpp"
#include "../src/chestnut/engine/macros.hpp"

#include "test_utils.hpp"


using namespace chestnut::engine;

TEST_CASE( "Audio - Audio manager test - general" )
{
    chestnutInit();


    CAudioManager manager;

    std::shared_ptr< CAudioResource > sfx;
    REQUIRE_NOTHROW( sfx = loadAudioResourceFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/audio/timgormly__8-bit-explosion2.aiff", EAudioResourceType::SFX ) );

    std::shared_ptr< CAudioResource > music;
    REQUIRE_NOTHROW( music = loadAudioResourceFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/audio/puredesigngirl__dramatic-music.mp3", EAudioResourceType::MUSIC ) );


    SECTION( "Add-get-remove" )
    {
        REQUIRE_FALSE( manager.getAudio( "sfx" ) );
        REQUIRE_FALSE( manager.getAudio( "music" ) );

        manager.addAudio( sfx, "sfx" );
        REQUIRE( manager.getAudio( "sfx" ) );
        REQUIRE_FALSE( manager.getAudio( "music" ) );

        manager.addAudio( music, "music" );
        REQUIRE( manager.getAudio( "sfx" ) );
        REQUIRE( manager.getAudio( "music" ) );

        manager.removeAudio( "sfx" );
        REQUIRE_FALSE( manager.getAudio( "sfx" ) );
        REQUIRE( manager.getAudio( "music" ) );
    }


    chestnutQuit();
}


TEST_CASE( "Audio - Audio manager test - SFX", "[manual]" )
{
    const char *testTitle = "Audio manager test - SFX";

    chestnutInit();


    CAudioManager manager;

    std::shared_ptr< CAudioResource > sfx;
    REQUIRE_NOTHROW( sfx = loadAudioResourceFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/audio/timgormly__8-bit-explosion2.aiff", EAudioResourceType::SFX ) );

    manager.addAudio( sfx, "sfx" );


    SECTION( "Play SFX once" )
    {
        showInfoMessageBox( testTitle, "Continue to play a sound effect once" );
        REQUIRE( manager.playSFX( "sfx" ) >= 0 );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Play SFX in loop for 2 seconds" )
    {
        showInfoMessageBox( testTitle, "Continue to play a sound effect in loop for 2 seconds" );
        REQUIRE( manager.playSFXFor( "sfx", 2.f, -1, -1 ) >= 0 );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Reduce global and SFX volume" )
    {
        audiochannel_t ch = manager.playSFX( "sfx", -1, -1 );
        REQUIRE( ch >= 0 );
        showInfoMessageBox( testTitle, "Continue to reduce the SFX volume by 50%" );
        manager.setSFXVolume( ch, 0.5f );
        showInfoMessageBox( testTitle, "Continue to reduce the global volume by 50%" );
        manager.setGlobalVolume( 0.5f );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Pausing SFX" )
    {
        audiochannel_t ch = manager.playSFX( "sfx", -1, -1 );
        REQUIRE( ch >= 0 );
        showInfoMessageBox( testTitle, "Click to pause the SFX" );
        manager.pauseSFX( ch );
        showInfoMessageBox( testTitle, "Click to resume the SFX" );
        manager.resumeSFX( ch );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Stopping SFX" )
    {
        audiochannel_t ch = manager.playSFX( "sfx", -1, -1 );
        REQUIRE( ch >= 0 );
        showInfoMessageBox( testTitle, "Click to stop the SFX" );
        manager.stopSFX( ch );
        showInfoMessageBox( testTitle, "Click to try to resume the SFX. This shouldn't do anything." );
        manager.resumeSFX( ch );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }


    chestnutQuit();

    sleepFor(1000);
}


TEST_CASE( "Audio - Audio manager test - music", "[manual]" )
{
    const char *testTitle = "Audio manager test - music";

    chestnutInit();


    CAudioManager manager;

    std::shared_ptr< CAudioResource > music;
    REQUIRE_NOTHROW( music = loadAudioResourceFromFile( CHESTNUT_ENGINE_ASSETS_DIR_PATH"/audio/puredesigngirl__dramatic-music.mp3", EAudioResourceType::MUSIC ) );

    manager.addAudio( music, "music" );


    SECTION( "Play music once" )
    {
        showInfoMessageBox( testTitle, "Continue to play some music" );
        manager.playMusic( "music" );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Reduce global and music volume" )
    {
        manager.playMusic( "music" );
        showInfoMessageBox( testTitle, "Continue to reduce the music volume by 50%" );
        manager.setMusicVolume( 0.5f );
        showInfoMessageBox( testTitle, "Continue to reduce the global volume by 50%" );
        manager.setGlobalVolume( 0.5f );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Pausing music" )
    {
        manager.playMusic( "music" );
        showInfoMessageBox( testTitle, "Click to pause the music" );
        manager.pauseMusic();
        showInfoMessageBox( testTitle, "Click to resume the music" );
        manager.resumeMusic();
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Stopping music" )
    {
        manager.playMusic( "music" );
        showInfoMessageBox( testTitle, "Click to stop the music" );
        manager.stopMusic();
        showInfoMessageBox( testTitle, "Click to try to resume the music. This shouldn't do anything." );
        manager.resumeMusic();
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }


    chestnutQuit();
}