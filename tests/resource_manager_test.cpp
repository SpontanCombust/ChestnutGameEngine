#include <catch2/catch.hpp>

#include "chestnut/engine/resources/resource.hpp"
#include "chestnut/engine/resources/resource_manager.hpp"


using namespace chestnut::engine;

const std::filesystem::path PATH1 = std::filesystem::absolute("./some/path");
const std::filesystem::path PATH2 = std::filesystem::absolute("./some/other/path");
const std::filesystem::path PATH_ERROR  = std::filesystem::absolute("./some/error/path");

class CMockResource1 : public IResource
{
public:
    static tl::expected<std::shared_ptr<CMockResource1>, std::string>
    loadNotFromFile()
    {
        auto resource = std::shared_ptr<CMockResource1>(new CMockResource1(tl::nullopt));
        return resource;
    }

    static tl::expected<std::shared_ptr<CMockResource1>, std::string> 
    loadFromFile(std::filesystem::path location) noexcept
    {
        auto resource = std::shared_ptr<CMockResource1>(new CMockResource1(location));
        return resource;
    }

    static tl::expected<std::shared_ptr<CMockResource1>, std::string> 
    load(std::filesystem::path location) noexcept
    {
        return loadFromFile(location);
    }

private:
    CMockResource1(tl::optional<std::filesystem::path> location) noexcept
    : IResource(location)
    {

    }
};

class CMockResource2 : public IResource
{
public:
    static tl::expected<std::shared_ptr<CMockResource2>, std::string> 
    load(std::filesystem::path location) noexcept
    {
        if(location == PATH_ERROR)
        {
            return tl::make_unexpected("error");
        }

        return std::shared_ptr<CMockResource2>(new CMockResource2(location));
    }

private:
    CMockResource2(tl::optional<std::filesystem::path> location) noexcept
    : IResource(location)
    {

    }
};





TEST_CASE("Resources - Resource manager test")
{
    CResourceManager rm;

    SECTION("loadResource")
    {
        REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH1));
        REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH2));

        auto res1 = rm.loadResource<CMockResource1>(PATH1);
        REQUIRE(res1.has_value());
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH1));

        auto res2 = rm.loadResource<CMockResource1>(PATH1);
        REQUIRE(res2.has_value());
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH1));

        // with loadResource manager should load a resource at the path again even if it has been loaded before
        REQUIRE(*res1 != *res2);

        // resources of different types should be able to be loaded for the same type at the same time
        auto res3 = rm.loadResource<CMockResource2>(PATH1);
        REQUIRE(res3.has_value());
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH1));
        REQUIRE(rm.isResourceLoaded<CMockResource2>(PATH1));

        // test for different location
        rm.loadResource<CMockResource1>(PATH2);
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH1));
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH2));
        REQUIRE(rm.isResourceLoaded<CMockResource2>(PATH1));

        // test for error when loading
        auto res4 = rm.loadResource<CMockResource2>(PATH_ERROR);
        REQUIRE_FALSE(res4.has_value());
        REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH_ERROR));
    }

    SECTION("getResource")
    {
        auto res1 = rm.getResource<CMockResource1>(PATH1);
        REQUIRE_FALSE(res1.has_value());

        rm.loadResource<CMockResource1>(PATH1);
        auto res2 = rm.getResource<CMockResource1>(PATH1);
        REQUIRE(res2.has_value());
    }

    SECTION("getOrLoadResource")
    {
        REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH1));
        REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH2));

        auto res1 = rm.getOrLoadResource<CMockResource1>(PATH1);
        REQUIRE(res1.has_value());

        auto res2 = rm.getOrLoadResource<CMockResource1>(PATH1);
        REQUIRE(res2.has_value());

        // if it was loaded before it should only get that resource 
        REQUIRE(*res1 == *res2);

        // resources of different types should be able to be loaded for the same type at the same time
        auto res3 = rm.getOrLoadResource<CMockResource2>(PATH1);
        REQUIRE(res3.has_value());
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH1));
        REQUIRE(rm.isResourceLoaded<CMockResource2>(PATH1));

        // test for different locations
        rm.getOrLoadResource<CMockResource1>(PATH2);
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH1));
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH2));
        REQUIRE(rm.isResourceLoaded<CMockResource2>(PATH1));
    }

    SECTION("addResource")
    {
        REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH1));

        // test for invalid resource
        auto ret1 = rm.addResource<CMockResource1>(nullptr);
        REQUIRE_FALSE(ret1.has_value());

        auto p1 = PATH1;
        auto p2 = p1;

        auto res1 = CMockResource1::loadFromFile(PATH1).value();
        auto ret2 = rm.addResource(res1);
        REQUIRE(ret2.has_value());
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH1));

        // test for the same location
        auto ret3 = rm.addResource(res1);
        REQUIRE_FALSE(ret3.has_value());
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH1));

        // ... and a different location
        auto res2 = CMockResource1::loadFromFile(PATH2).value();
        auto ret4 = rm.addResource(res2);
        REQUIRE(ret4.has_value());
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH2));

        // test for custom location
        auto ret5 = rm.addResource(res2, "completely/different/location");
        REQUIRE(ret5.has_value());
    }

    SECTION("freeResource")
    {
        REQUIRE_FALSE(rm.freeResource<CMockResource1>(PATH1));

        auto res1 = rm.loadResource<CMockResource1>(PATH1);
        REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH1));
        REQUIRE(res1->use_count() == 2);

        REQUIRE(rm.freeResource<CMockResource1>(PATH1));
        REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH1));
        REQUIRE(res1->use_count() == 1);
    }

    SECTION("freeUnusedResources")
    {
        REQUIRE(rm.freeUnusedResources() == 0);

        {
            auto res1 = rm.loadResource<CMockResource1>(PATH1);
            (void)rm.loadResource<CMockResource1>(PATH2); // return value is not stored here

            REQUIRE(rm.freeUnusedResources() == 1);
            REQUIRE(rm.isResourceLoaded<CMockResource1>(PATH1));
            REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH2));

            // res1 goes out of scope
        }

        REQUIRE(rm.freeUnusedResources() == 1);
        REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH1));
        REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH2));
    }

    SECTION("freeAllResources")
    {
        auto res1 = rm.loadResource<CMockResource1>(PATH1);
        auto res2 = rm.loadResource<CMockResource1>(PATH2);

        REQUIRE(res1->use_count() == 2);
        REQUIRE(res2->use_count() == 2);

        rm.freeAllResources();

        REQUIRE(res1->use_count() == 1);
        REQUIRE(res2->use_count() == 1);
        REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH1));
        REQUIRE_FALSE(rm.isResourceLoaded<CMockResource1>(PATH2));
    }
}