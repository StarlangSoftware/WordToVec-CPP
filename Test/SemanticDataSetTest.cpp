//
// Created by Olcay Taner YILDIZ on 15.11.2022.
//

#include "catch.hpp"
#include "../src/SemanticDataSet.h"

TEST_CASE("SemanticDataSetTest-testSpearman") {
    SemanticDataSet semanticDataSet = SemanticDataSet("AnlamverRel.txt");
    REQUIRE_FALSE(1.0 != semanticDataSet.spearmanCorrelation(semanticDataSet));
    semanticDataSet = SemanticDataSet("MC.txt");
    REQUIRE_FALSE(1.0 != semanticDataSet.spearmanCorrelation(semanticDataSet));
    semanticDataSet = SemanticDataSet("MEN.txt");
    REQUIRE_FALSE(1.0 != semanticDataSet.spearmanCorrelation(semanticDataSet));
    semanticDataSet = SemanticDataSet("MTurk771.txt");
    REQUIRE_FALSE(1.0 != semanticDataSet.spearmanCorrelation(semanticDataSet));
    semanticDataSet = SemanticDataSet("RareWords.txt");
    REQUIRE_FALSE(1.0 != semanticDataSet.spearmanCorrelation(semanticDataSet));
    semanticDataSet = SemanticDataSet("RG.txt");
    REQUIRE_FALSE(1.0 != semanticDataSet.spearmanCorrelation(semanticDataSet));
}