#include <vector>
#include "Enigma.h"

// =====================================================================================================================
//              oooooooooooo ooooo      ooo ooooo   .oooooo.    ooo        ooooo       .o.
//              `888'     `8 `888b.     `8' `888'  d8P'  `Y8b   `88.       .888'      .888.
//              888          8 `88b.    8   888  888            888b     d'888      .8"888.
//              888oooo8     8   `88b.  8   888  888            8 Y88. .P  888     .8' `888.
//              888    "     8     `88b.8   888  888     ooooo  8  `888'   888    .88ooo8888.
//              888       o  8       `888   888  `88.    .88'   8    Y     888   .8'     `888.
//              o888ooooood8 o8o        `8  o888o  `Y8bood8P'   o8o        o888o o88o     o8888o
// =====================================================================================================================
//      Fill in the given crib and the first n characters of the input-string, recall that n has to be equal to the size
//      of the crib. The rotor combinations need to be calculated by hand and filled in, same for the reflector.
//      All checks need to be done manually in ''Enigma::advancedTuringBombe()'', more information there.
//      No optimalization has been done so to check all combinations, an average of 3 hours is needed.
// =====================================================================================================================

int main() {
    std::string input_str = "LXCACYLPNSIZCOQMAZ";
    std::string crib = "DEOPGAVEVOORENIGMA";
    std::vector<std::vector<std::string>> rotor_cycles = {
            {"BJ", "CDKLHUP", "ESZ", "FIXVYOMW", "GR", "NT"},
            {"AELTPHQXRU", "BKNW", "CMOY", "DFG", "IV", "JZ"},
            {"ABDHPEJT", "CFLVMZOYQIRWUKXSG"},
            {"ATV", "BHKOXYDQMNFI", "CEULWZG", "JRP"},
            {"AXQCNDTHSGEIOVLWMUJKRFPB"},
    };
    std::vector<std::string> reflector = {"AY", "BR", "CU", "DH", "EQ", "FS", "GL", "IP", "JX", "KN", "MO", "TZ", "VW"};
    auto* enigma = new Enigma(crib, input_str, reflector, rotor_cycles);
    enigma->decrypt();
    return 0;
}
