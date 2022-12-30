#include <catch2/catch.hpp>

#include "chestnut/engine/init.hpp"
#include "chestnut/engine/audio/audio_manager.hpp"
#include "chestnut/engine/misc/utility_functions.hpp"

#include "test_utils.hpp"


using namespace chestnut::engine;

TEST_CASE( "Audio - Audio manager test - general" )
{
    chestnutInit();


    CAudioManager manager;

    SECTION("Music")
    {
        std::shared_ptr<CMusicResource> music;
        REQUIRE_NOTHROW(music = CMusicResource::load(assetPathToAbsolute("testing/audio/dramatic-music.mp3")).value());

        // doesn't have music yet
        REQUIRE_FALSE(manager.hasMusic("dramatic-music"));
        REQUIRE_FALSE(manager.removeMusic("dramatic-music"));

        // add music
        REQUIRE(manager.addAudio(music));
        REQUIRE(manager.hasMusic("dramatic-music"));

        // music is already present
        REQUIRE_FALSE(manager.addAudio(music));

        // remove music
        REQUIRE(manager.removeMusic("dramatic-music"));
        REQUIRE_FALSE(manager.hasMusic("dramatic-music"));
    }

    SECTION("SFX")
    {
        std::shared_ptr<CSoundBankResource> soundBank;
        REQUIRE_NOTHROW(soundBank = CSoundBankResource::load(assetPathToAbsolute("testing/audio/sounds.bnk")).value());

        // doesn't have sound bank yet
        REQUIRE_FALSE(manager.hasSoundBank("sounds"));
        REQUIRE_FALSE(manager.removeSoundBank("sounds"));
        REQUIRE_FALSE(manager.hasSFX("explosion"));
        REQUIRE_FALSE(manager.hasSFX("hurt"));
        REQUIRE_FALSE(manager.hasSFX("sword-slash"));

        // bank is added
        REQUIRE(manager.addAudio(soundBank));
        REQUIRE(manager.hasSoundBank("sounds"));
        REQUIRE(manager.hasSFX("explosion"));
        REQUIRE(manager.hasSFX("hurt"));
        REQUIRE(manager.hasSFX("sword-slash"));

        // bank is already present
        REQUIRE_FALSE(manager.addAudio(soundBank));

        // remove bank
        REQUIRE(manager.removeSoundBank("sounds"));
        REQUIRE_FALSE(manager.hasSoundBank("sounds"));
        REQUIRE_FALSE(manager.hasSFX("explosion"));
        REQUIRE_FALSE(manager.hasSFX("hurt"));
        REQUIRE_FALSE(manager.hasSFX("sword-slash"));
    }

    chestnutQuit();
}


TEST_CASE( "Audio - Audio manager test - SFX", "[manual]" )
{
    const char *testTitle = "Audio manager test - SFX";

    chestnutInit();


    CAudioManager manager;

    std::shared_ptr<CSoundBankResource> bnk;
    REQUIRE_NOTHROW(bnk = CSoundBankResource::load(assetPathToAbsolute("testing/audio/sounds.bnk")).value());

    manager.addAudio(bnk);


    SECTION( "Play SFX once" )
    {
        showInfoMessageBox( testTitle, "Continue to play a sound effect once" );
        REQUIRE( manager.playSFX( "explosion" ) >= 0 );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Play SFX 3 times" )
    {
        showInfoMessageBox( testTitle, "Continue to play a sound effect 3 times" );
        REQUIRE( manager.playSFX( "explosion", 3 ) >= 0 );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Play SFX in loop for 2 seconds" )
    {
        showInfoMessageBox( testTitle, "Continue to play a sound effect in loop for 2 seconds" );
        REQUIRE( manager.playSFXFor( "explosion", 2.f, -1 ) >= 0 );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Reduce global and SFX volume" )
    {
        audiochannel_t ch = manager.playSFX( "hurt", -1 );
        REQUIRE( ch >= 0 );
        showInfoMessageBox( testTitle, "Continue to reduce the SFX volume by 50%" );
        manager.setSFXVolume( ch, 0.5f );
        showInfoMessageBox( testTitle, "Continue to reduce the global volume by 50%" );
        manager.setGlobalVolume( 0.5f );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Pausing SFX" )
    {
        audiochannel_t ch = manager.playSFX( "hurt", -1 );
        REQUIRE( ch >= 0 );
        showInfoMessageBox( testTitle, "Click to pause the SFX" );
        manager.pauseSFX( ch );
        showInfoMessageBox( testTitle, "Click to resume the SFX" );
        manager.resumeSFX( ch );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Stopping SFX" )
    {
        audiochannel_t ch = manager.playSFX( "sword-slash", -1 );
        REQUIRE( ch >= 0 );
        showInfoMessageBox( testTitle, "Click to stop the SFX" );
        manager.stopSFX( ch );
        showInfoMessageBox( testTitle, "Click to try to resume the SFX. This shouldn't do anything." );
        manager.resumeSFX( ch );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }


    chestnutQuit();

    // add delay between sections
    sleepFor(1000);
}


TEST_CASE( "Audio - Audio manager test - music", "[manual]" )
{
    const char *testTitle = "Audio manager test - music";

    chestnutInit();


    CAudioManager manager;

    std::shared_ptr<CMusicResource> music;
    REQUIRE_NOTHROW(music = CMusicResource::load(assetPathToAbsolute("testing/audio/dramatic-music.mp3")).value());

    manager.addAudio(music);


    SECTION( "Play music once" )
    {
        showInfoMessageBox( testTitle, "Continue to play some music" );
        manager.playMusic( "dramatic-music" );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Reduce global and music volume" )
    {
        manager.playMusic( "dramatic-music" );
        showInfoMessageBox( testTitle, "Continue to reduce the music volume by 50%" );
        manager.setMusicVolume( 0.5f );
        showInfoMessageBox( testTitle, "Continue to reduce the global volume by 50%" );
        manager.setGlobalVolume( 0.5f );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Pausing music" )
    {
        manager.playMusic( "dramatic-music" );
        showInfoMessageBox( testTitle, "Click to pause the music" );
        manager.pauseMusic();
        showInfoMessageBox( testTitle, "Click to resume the music" );
        manager.resumeMusic();
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Stopping music" )
    {
        manager.playMusic( "dramatic-music" );
        showInfoMessageBox( testTitle, "Click to stop the music" );
        manager.stopMusic();
        showInfoMessageBox( testTitle, "Click to try to resume the music. This shouldn't do anything." );
        manager.resumeMusic();
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Fade in music" )
    {
        showInfoMessageBox( testTitle, "Click to play music with 3 second fade in" );
        manager.playMusicFadeIn( "dramatic-music", 3.f );
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }

    SECTION( "Fade out music" )
    {
        manager.playMusic( "dramatic-music" );
        showInfoMessageBox( testTitle, "Click to fade out music over the course of 5 seconds" );
        manager.fadeOutMusic(5.f);
        REQUIRE( showConfirmMessageBox( testTitle ) );
    }


    chestnutQuit();
}