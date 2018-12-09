#include "SymbolTable.hpp"
namespace TPJparser {

    SymbolTable::SymbolTable() {}

    std::shared_ptr<SymbolTableItem> SymbolTable::defineVar(const std::string& name) {
        if (this->_table.count(name) == 0)
            return this->_table[name] = 
                std::make_shared<SymbolTableItem>
                    (name, SymbolTableItem::Kind::VARIABLE);

        return this->_table[name];
    }

    std::shared_ptr<SymbolTableItem> SymbolTable::defineFunc(const std::string& name) {
        if (this->_table.count(name) == 0)
            return this->_table[name] =
                std::make_shared<SymbolTableItem>
                    (name, SymbolTableItem::Kind::FUNCTION);

        return this->_table[name];
    }

    std::shared_ptr<SymbolTableItem> SymbolTable::getItemByName(const std::string& name) const {
        if (this->_table.count(name) == 0)
            return nullptr;

        return this->_table.at(name);
    }

    bool SymbolTable::isFuncDeclared(const std::string& name) const {
        const auto item = this->getItemByName(name);

        if (item.get() != nullptr) {
            if (item.get()->isFunc())
                return true;
        }
        return false;
    }

    bool SymbolTable::isVarDeclared(const std::string& name) const {
        const auto item = this->getItemByName(name);

        if (item.get() != nullptr) {
            if (item.get()->isVar())
                return true;
        }
        return false;
    }

    void SymbolTable::printContent() const {
        for (auto& item: this->_table) {
            item.second->print();
        }
    }
}