//
//  ALU.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 25.12.21.
//

#ifndef ALU_h
#define ALU_h

enum Operation {
    inp, add, mul, divi, mod, eql
};

struct Register {
    Register() {};
    Register(int z, int w) : z(z), w(w) {};
    int x = 0, y = 0, z = 0, w = 0;

    void set(std::string& var, int value) {
        if(var == "x") { x = value; }
        if(var == "y") { y = value; }
        if(var == "z") { z = value; }
        if(var == "w") { w = value; }
    }

    int get(std::string& var) {
        if(var == "x") { return x; }
        if(var == "y") { return y; }
        if(var == "z") { return z; }
        if(var == "w") { return w; }
        return var == "" ? 0 : std::stoi(var);
    }

    bool valid() {
        return z == 0;
    }

    bool operator==(const Register& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
    }
};

struct Instruction {
    Instruction(std::string &o, std::string& f, std::string& s) : first(f), second(s) {
        operation = parse(o);
    }

    Operation operation;
    std::string first;
    std::string second;

    Register process(Register &r, int input) {
        Register rNew = r;
        auto f = rNew.get(first);
        auto s = operation == inp ? input : rNew.get(second);
        rNew.set(first, value(f, s));
        return rNew;
    }

    int value(int a, int b) {
        switch(operation) {
            case inp: { return b; }
            case add: { return a + b; }
            case mul: { return a * b; }
            case divi: { return a / b; }
            case mod: { return a % b; }
            case eql: { return a == b; }
        }
    }

    Operation parse(std::string& o) {
        if(o == "inp") return inp;
        if(o == "mul") return mul;
        if(o == "add") return add;
        if(o == "div") return divi;
        if(o == "mod") return mod;
        if(o == "eql") return eql;
        return inp;
    }

    bool isInput() {
        return operation == inp;
    }
};

struct InputSet {
    InputSet() {};
    InputSet(bool findLargest) : findLargest(findLargest) {};

    bool findLargest = true;
    int instructionStart = 0;
    std::vector<int> inputs = {};
    Register inputRegister = Register();

    std::vector<InputSet> followSets(std::vector<Instruction>& instructions) {
        std::vector<InputSet> newSets;

        if(instructionStart >= instructions.size()) {
            return {};
        }

        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        if(findLargest) {
            std::reverse(numbers.begin(), numbers.end());
        }

        for(int i : numbers) {
            InputSet f = *this;
            f.inputRegister = instructions[instructionStart].process(inputRegister, i);
            f.instructionStart = instructionStart + 1;
            f.inputs.push_back(i);

            while(f.instructionStart < instructions.size() && !instructions[f.instructionStart].isInput()) {
                f.inputRegister = instructions[f.instructionStart].process(f.inputRegister, 0);
                f.instructionStart++;
            }

            bool found = false;
            for(int j=0; j<newSets.size(); ++j) {
                if(newSets[j].key() == f.key()) {
                    found = true;
                    break;
                }
            }

            if(!found) {
                newSets.push_back(f);
            }

            if(instructionStart >= instructions.size()) {
                return newSets;
            }
        }

        std::reverse(newSets.begin(), newSets.end());

        return newSets;
    }

    bool isValid(std::vector<Instruction>& instructions) {
        return inputRegister.valid() && instructionStart >= instructions.size();
    }

    std::string key() {
        std::stringstream ss;
        ss << instructionStart << "-";
        ss << inputRegister.z << "-";
        ss << inputRegister.w;
        return ss.str();
    }
};

#endif /* ALU_h */
