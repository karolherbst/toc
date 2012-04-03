# copyright ToC

inherit toc

DESCRIPTION="a collection of various template based classes"

src_test() {
    cd "${CMAKE_BUILD_DIR}" || die
    Xemake test
}
