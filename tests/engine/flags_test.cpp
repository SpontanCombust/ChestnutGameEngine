#include <catch2/catch.hpp>

#include "chestnut/engine/misc/flags.hpp"


using namespace chestnut::engine;

enum class F
{
    ALPHA,
    BRAVO,
    CHARLIE,
    DELTA
};

TEST_CASE( "Misc - Flags test" )
{
    SECTION("Default state")
    {
        CFlags<F> f;

        REQUIRE(f.m_buffer == 0);
        REQUIRE(f.empty());
        REQUIRE(!f);
    }

    SECTION("Constructors")
    {
        CFlags<F> f1;
        REQUIRE(f1.m_buffer == 0);
        REQUIRE(f1.empty());
        REQUIRE(!f1);

        CFlags<F> f2(F::CHARLIE);
        REQUIRE(f2.m_buffer == (1 << static_cast<int>(F::CHARLIE)));
        REQUIRE(!f2.empty());
        REQUIRE(f2);

        CFlags<F> f3({F::ALPHA, F::CHARLIE});
        REQUIRE(f3.m_buffer == ((1 << static_cast<int>(F::ALPHA)) | ( 1<< static_cast<int>(F::CHARLIE))));
        REQUIRE(!f3.empty());
        REQUIRE(f3);
    }

    SECTION("Equality operator")
    {
        CFlags<F> f1(F::ALPHA);
        CFlags<F> f2(F::BRAVO);
        CFlags<F> f3{F::BRAVO, F::CHARLIE};

        REQUIRE(f1 == f1);
        REQUIRE(f1 != f2);
        REQUIRE(f2 == f2);
        REQUIRE(f2 != f3);
    }

    SECTION("OR operator")
    {
        REQUIRE(CFlags{F::ALPHA} == (CFlags<F>() | CFlags{F::ALPHA}));
        REQUIRE(CFlags{F::ALPHA, F::CHARLIE} == (CFlags(F::ALPHA) | F::CHARLIE));
        REQUIRE(CFlags{F::ALPHA} != (CFlags(F::ALPHA) | F::CHARLIE));
    }

    SECTION("AND operator")
    {
        CFlags<F> f0{F::CHARLIE};
        CFlags<F> f1{F::ALPHA, F::BRAVO};
        CFlags<F> f2{F::ALPHA, F::BRAVO, F::DELTA};
        CFlags<F> f3{F::CHARLIE, F::DELTA};

        REQUIRE((f0 & CFlags<F>()) == CFlags<F>());
        REQUIRE((f1 & CFlags<F>()) == CFlags<F>());
        REQUIRE((f2 & CFlags<F>()) == CFlags<F>());
        REQUIRE((f0 & f1) == (CFlags<F>()));
        REQUIRE((f0 & f2) == (CFlags<F>()));
        REQUIRE((f0 & f3) == (CFlags(F::CHARLIE)));
        REQUIRE((f1 & f2) == (CFlags(F::ALPHA) | F::BRAVO));
        REQUIRE((f1 & f3) == (CFlags<F>()));
        REQUIRE((f2 & f3) == (CFlags(F::DELTA)));
    }

    SECTION("XOR operator")
    {
        CFlags<F> f0{F::CHARLIE};
        CFlags<F> f1{F::ALPHA, F::BRAVO};
        CFlags<F> f2{F::ALPHA, F::BRAVO, F::DELTA};
        CFlags<F> f3{F::CHARLIE, F::DELTA};

        REQUIRE((f0 ^ CFlags<F>()) == f0);
        REQUIRE((f1 ^ CFlags<F>()) == f1);
        REQUIRE((f2 ^ CFlags<F>()) == f2);
        REQUIRE((f0 ^ f1) == (CFlags{F::ALPHA, F::BRAVO, F::CHARLIE}));
        REQUIRE((f0 ^ f2) == (CFlags{F::ALPHA, F::BRAVO, F::CHARLIE, F::DELTA}));
        REQUIRE((f0 ^ f3) == (CFlags(F::DELTA)));
        REQUIRE((f1 ^ f2) == (CFlags(F::DELTA)));
        REQUIRE((f1 ^ f3) == (CFlags{F::ALPHA, F::BRAVO, F::CHARLIE, F::DELTA}));
        REQUIRE((f2 ^ f3) == (CFlags{F::ALPHA, F::BRAVO, F::CHARLIE}));
    }    
}