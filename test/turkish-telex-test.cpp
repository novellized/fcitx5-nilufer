#include "key_processor.h"
#include "utf8.h"

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

void testTurkishTelex() {
    lotus::KeyProcessor kp;

    auto                typeStr = [&](const std::string& input) {
        for (char c : input) {
            kp.processKey(static_cast<uint32_t>(c), {});
        }
    };

    auto getPreeditUtf8 = [&]() { return lotus::utf8::encode(kp.preedit()); };

    auto getCommitUtf8 = [&]() { return lotus::utf8::encode(kp.takeCommit()); };

    // Test 1: Single letter transformations (lowercase)
    {
        kp.reset();
        typeStr("cw");
        assert(getPreeditUtf8() == "ç");

        kp.reset();
        typeStr("sw");
        assert(getPreeditUtf8() == "ş");

        kp.reset();
        typeStr("gw");
        assert(getPreeditUtf8() == "ğ");

        kp.reset();
        typeStr("uw");
        assert(getPreeditUtf8() == "ü");

        kp.reset();
        typeStr("ow");
        assert(getPreeditUtf8() == "ö");

        kp.reset();
        typeStr("iw");
        assert(getPreeditUtf8() == "ı");
    }

    // Test 2: Uppercase transformations
    {
        kp.reset();
        typeStr("Cw");
        assert(getPreeditUtf8() == "Ç");

        kp.reset();
        typeStr("CW");
        assert(getPreeditUtf8() == "Ç");

        kp.reset();
        typeStr("Sw");
        assert(getPreeditUtf8() == "Ş");

        kp.reset();
        typeStr("Gw");
        assert(getPreeditUtf8() == "Ğ");

        kp.reset();
        typeStr("Uw");
        assert(getPreeditUtf8() == "Ü");

        kp.reset();
        typeStr("Ow");
        assert(getPreeditUtf8() == "Ö");

        kp.reset();
        typeStr("Iw");
        assert(getPreeditUtf8() == "İ");

        kp.reset();
        typeStr("IW");
        assert(getPreeditUtf8() == "İ");
    }

    // Test 3: Revert / Undo on pressing 'w' again
    {
        kp.reset();
        typeStr("cww");
        assert(getPreeditUtf8() == "cw");

        kp.reset();
        typeStr("sww");
        assert(getPreeditUtf8() == "sw");

        kp.reset();
        typeStr("gww");
        assert(getPreeditUtf8() == "gw");

        kp.reset();
        typeStr("uww");
        assert(getPreeditUtf8() == "uw");

        kp.reset();
        typeStr("oww");
        assert(getPreeditUtf8() == "ow");

        kp.reset();
        typeStr("iww");
        assert(getPreeditUtf8() == "iw");

        kp.reset();
        typeStr("Cww");
        assert(getPreeditUtf8() == "Cw");

        kp.reset();
        typeStr("Iww");
        assert(getPreeditUtf8() == "Iw");
    }

    // Test 4: Full Turkish words
    {
        // teşekkür
        kp.reset();
        typeStr("teswekkuwr");
        assert(getPreeditUtf8() == "teşekkür");

        // çocuk
        kp.reset();
        typeStr("cwocuk");
        assert(getPreeditUtf8() == "çocuk");

        // öğrenci
        kp.reset();
        typeStr("owgwrenci");
        assert(getPreeditUtf8() == "öğrenci");

        // güneş
        kp.reset();
        typeStr("guwnesw");
        assert(getPreeditUtf8() == "güneş");

        // ılık
        kp.reset();
        typeStr("iwliwk");
        assert(getPreeditUtf8() == "ılık");

        // İstanbul
        kp.reset();
        typeStr("Iwstanbul");
        assert(getPreeditUtf8() == "İstanbul");

        // Türkçe
        kp.reset();
        typeStr("Tuwrkcwe");
        assert(getPreeditUtf8() == "Türkçe");
    }

    // Test 5: Backspace handling
    {
        kp.reset();
        typeStr("cw");
        assert(getPreeditUtf8() == "ç");
        kp.processKey(lotus::kFcitxBackSpace, {});
        assert(getPreeditUtf8().empty());

        kp.reset();
        typeStr("teswe"); // teşe
        assert(getPreeditUtf8() == "teşe");
        kp.processKey(lotus::kFcitxBackSpace, {});
        assert(getPreeditUtf8() == "teş");
        kp.processKey(lotus::kFcitxBackSpace, {});
        assert(getPreeditUtf8() == "te");
    }

    // Test 6: Space and word break commit
    {
        kp.reset();
        typeStr("teswekkuwr");
        assert(getPreeditUtf8() == "teşekkür");
        kp.processKey(lotus::kFcitxSpace, {});
        assert(getCommitUtf8() == "teşekkür ");
        assert(getPreeditUtf8().empty());
    }

    // Test 7: rebuildFromText
    {
        kp.reset();
        kp.rebuildFromText(lotus::utf8::decode("ç"));
        assert(getPreeditUtf8() == "ç");
        // Pressing 'w' on existing 'ç' reverts it to "cw"
        kp.processKey(static_cast<uint32_t>('w'), {});
        assert(getPreeditUtf8() == "cw");
    }

    std::cout << "All Turkish Telex tests PASSED successfully!" << std::endl;
}

int main() {
    testTurkishTelex();
    return 0;
}
