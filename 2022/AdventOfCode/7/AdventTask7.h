//
//  AdventTask7.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 07.12.21.
//

#ifndef AdventTask7_h
#define AdventTask7_h

#include <AdventTask.h>

class File {
  public:
    File(const std::string& name, bool folder, int64_t size, std::shared_ptr<File> parent) : name(name), folder(folder), size(size), parent(parent) {};

    std::string name;
    bool folder;
    int64_t size;
    std::vector<std::shared_ptr<File>> files;
    std::shared_ptr<File> parent;
};

class AdventTask7 : public AdventTask<7> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        auto current = parseFiles(file);
        std::cout << calculateSum(current) << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        auto current = parseFiles(file);

        auto needed = 30000000 - (70000000 - current->size);

        int64_t min = std::numeric_limits<int64_t>::max();
        calculateMinNeeded(current, needed, min);

        std::cout << min << std::endl;
    }

    int64_t calculateFileSize(std::shared_ptr<File> f) {
        if(f->folder) {
            int64_t sum = 0;
            for(auto& sub : f->files) {
                sum += calculateFileSize(sub);
            }

            f->size = sum;
            return sum;
        } else {
            return f->size;
        }
    }

    int64_t calculateSum(std::shared_ptr<File> f) {
        if(!f->folder) { return 0; }

        int64_t sum = f->size <= 100000 ? f->size : 0;

        for(auto& sub : f->files) {
            sum += calculateSum(sub);
        }

        return sum;
    }

    void calculateMinNeeded(std::shared_ptr<File> f, int64_t needed, int64_t &min) {
        if(!f->folder) { return; }

        if(f->size > needed && f->size < min) {
            min = f->size;
        }

        for(auto& sub : f->files) {
            calculateMinNeeded(sub, needed, min);
        }
    };

    std::shared_ptr<File> parseFiles(std::ifstream &file) {
        std::string t1, t2;

        auto current = std::make_shared<File>("", true, 0, nullptr);
        current->folder = true;

        while (file >> t1 >> t2) {
            if(t1 == "$") {
                if(t2 == "cd") {
                    std::string f;
                    file >> f;

                    if(f == "..") {
                        current = current->parent;
                    } else {
                        for(auto& t : current->files) {
                            if(t->name == f) {
                                current = t;
                                break;
                            }
                        }
                    }
                }
            } else {
                bool folder = t1 == "dir";
                int64_t size = folder ? 0 : std::stoi(t1);

                auto f = std::make_shared<File>(t2, folder, size, current);
                current->files.push_back(f);
            }
        }

        while(current->parent) {
            current = current->parent;
        }

        calculateFileSize(current);

        return current;
    }
};

#endif /* AdventTask7_h */
