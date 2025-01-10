#include "catch2/catch_test_macros.hpp"
#include "catch2/generators/catch_generators.hpp"

#include "vpr_api.h"

namespace {

static constexpr const char kArchFile[] = "../../vtr_flow/arch/timing/k6_frac_N10_mem32K_40nm.xml";

static constexpr const char kRrGraphFile[] = "test_capnp.rr_graph.bin";
static constexpr const char kPlaceDelayFile[] = "test_capnp.place_delay.bin";
static constexpr const char kLookaheadFile[] = "test_capnp.lookahead.bin";

TEST_CASE("read_rr_graph", "[vpr]") {
    {
        t_vpr_setup vpr_setup = t_vpr_setup();
        t_arch arch = t_arch();
        t_options options = t_options();
        const char* argv[] = {
            "test_vpr",
            kArchFile,
            "wire.eblif",
            "--route_chan_width",
            "100",
            "--write_rr_graph",
            kRrGraphFile};
        vpr_init(sizeof(argv) / sizeof(argv[0]), argv,
                 &options, &vpr_setup, &arch);
        REQUIRE(vpr_flow(vpr_setup, arch));
        vpr_free_all(arch, vpr_setup);
    }

    t_vpr_setup vpr_setup = t_vpr_setup();
    t_arch arch = t_arch();
    t_options options = t_options();
    const char* argv[] = {
        "test_vpr",
        kArchFile,
        "wire.eblif",
        "--route_chan_width",
        "100",
        "--read_rr_graph",
        kRrGraphFile};
    vpr_init(sizeof(argv) / sizeof(argv[0]), argv,
             &options, &vpr_setup, &arch);
    REQUIRE(vpr_flow(vpr_setup, arch));
    vpr_free_all(arch, vpr_setup);
}

TEST_CASE("read_placement_delay_lookup", "[vpr]") {
    {
        t_vpr_setup vpr_setup = t_vpr_setup();
        t_arch arch = t_arch();
        t_options options = t_options();
        const char* argv[] = {
            "test_vpr",
            kArchFile,
            "wire.eblif",
            "--route_chan_width",
            "100",
            "--write_placement_delay_lookup",
            kPlaceDelayFile};
        vpr_init(sizeof(argv) / sizeof(argv[0]), argv,
                 &options, &vpr_setup, &arch);
        REQUIRE(vpr_flow(vpr_setup, arch));
        vpr_free_all(arch, vpr_setup);
    }

    t_vpr_setup vpr_setup = t_vpr_setup();
    t_arch arch = t_arch();
    t_options options = t_options();
    const char* argv[] = {
        "test_vpr",
        kArchFile,
        "wire.eblif",
        "--route_chan_width",
        "100",
        "--read_placement_delay_lookup",
        kPlaceDelayFile};
    vpr_init(sizeof(argv) / sizeof(argv[0]), argv,
             &options, &vpr_setup, &arch);
    REQUIRE(vpr_flow(vpr_setup, arch));
    vpr_free_all(arch, vpr_setup);
}

TEST_CASE("read_router_lookahead", "[vpr]") {
    // `classic` and `compressed_map` don't support capnp export.
    const char* lookahead_type = GENERATE("map", "extended_map");

    {
        t_vpr_setup vpr_setup = t_vpr_setup();
        t_arch arch = t_arch();
        t_options options = t_options();
        const char* argv[] = {
            "test_vpr",
            kArchFile,
            "wire.eblif",
            "--route_chan_width",
            "100",
            "--router_lookahead",
            lookahead_type,
            "--write_router_lookahead",
            kLookaheadFile};
        vpr_init(sizeof(argv) / sizeof(argv[0]), argv,
                 &options, &vpr_setup, &arch);
        REQUIRE(vpr_flow(vpr_setup, arch));
        vpr_free_all(arch, vpr_setup);
    }

    t_vpr_setup vpr_setup = t_vpr_setup();
    t_arch arch = t_arch();
    t_options options = t_options();
    const char* argv[] = {
        "test_vpr",
        kArchFile,
        "wire.eblif",
        "--route_chan_width",
        "100",
        "--router_lookahead",
        lookahead_type,
        "--read_router_lookahead",
        kLookaheadFile};
    vpr_init(sizeof(argv) / sizeof(argv[0]), argv,
             &options, &vpr_setup, &arch);
    REQUIRE(vpr_flow(vpr_setup, arch));
    vpr_free_all(arch, vpr_setup);
}

} // namespace
