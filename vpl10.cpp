#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Definição da classe Pokemon
class Pokemon {
protected:
    std::string _nome;
    std::string _tipo_ataque;
    double _forca_ataque;
    double _energia;
	//double dano;

public:
    Pokemon(std::string nome, std::string tipo_ataque, double forca_ataque)
        : _nome(nome), _tipo_ataque(tipo_ataque), _forca_ataque(forca_ataque), _energia(100) {}

    virtual ~Pokemon() = default;

    void falar_nome() const {
        std::cout << _nome << "!" << std::endl;
    }

    virtual void falar_tipo_ataque() const {
        std::cout << _tipo_ataque << "!" << std::endl;
    }

    void imprimir_status() const {
        std::cout << _nome << "!" << std::endl;
        std::cout << "Energia: " << _energia << std::endl;
    }

    void imprimir_informacoes() const {
        std::cout << "Pokemon: " << _nome << std::endl;
        std::cout << "Tipo ataque: " << _tipo_ataque << std::endl;
        std::cout << "Dano: " << calcular_dano() << std::endl;
        std::cout << "Energia: " << _energia << std::endl;
    }

    virtual double calcular_dano() const = 0;

    void atacar(Pokemon* outro_pokemon) {
        falar_nome();
        falar_tipo_ataque();
        double dano = calcular_dano();
        std::cout << "Dano: " << dano << std::endl;
        outro_pokemon->receber_dano(dano);
    }

    void receber_dano(double valor_dano) {
        _energia -= valor_dano;
        if (_energia < 0) _energia = 0;
        if (_energia == 0) std::cout << _nome << " morreu!" << std::endl;
    }

    std::string getNome() const { return _nome; }
};

// Definição da classe PokemonEletrico
class PokemonEletrico : public Pokemon {
private:
    double _potencia_raio;

public:
    PokemonEletrico(std::string nome, std::string tipo_ataque, double forca_ataque, double potencia_raio)
        : Pokemon(nome, tipo_ataque, forca_ataque), _potencia_raio(potencia_raio) {}

    void falar_tipo_ataque() const override {
        std::cout << _tipo_ataque << "!" << std::endl << "Bzzzz!" << std::endl;
    }

    double calcular_dano() const override {
        return ataque_eletrico();
    }

    double ataque_eletrico() const {
        return _forca_ataque * _potencia_raio;
    }
};

// Definição da classe PokemonAquatico
class PokemonAquatico : public Pokemon {
private:
    double _litros_jato;

public:
    PokemonAquatico(std::string nome, std::string tipo_ataque, double forca_ataque, double litros_jato)
        : Pokemon(nome, tipo_ataque, forca_ataque), _litros_jato(litros_jato) {}

    void falar_tipo_ataque() const override {
        std::cout << _tipo_ataque << "!" << std::endl << "Splash!" << std::endl;
    }

    double calcular_dano() const override {
        return ataque_aquatico();
    }

    double ataque_aquatico() const {
        return _forca_ataque + _litros_jato;
    }
};

// Definição da classe PokemonExplosivo
class PokemonExplosivo : public Pokemon {
private:
    double _temperatura_explosao;

public:
    PokemonExplosivo(std::string nome, std::string tipo_ataque, double forca_ataque, double temperatura_explosao)
        : Pokemon(nome, tipo_ataque, forca_ataque), _temperatura_explosao(temperatura_explosao) {}

    void falar_tipo_ataque() const override {
        std::cout << _tipo_ataque << "!" << std::endl << "Boom!" << std::endl;
    }

    double calcular_dano() const override {
        return ataque_explosivo();
    }

    double ataque_explosivo() const {
        return _forca_ataque / _temperatura_explosao;
    }
};

// Definição da classe Treinador
class Treinador {
private:
    std::string _nome;
    std::vector<Pokemon*> _pokemons;

public:
    Treinador(std::string nome) : _nome(nome) {}

    ~Treinador() {
        for (Pokemon* p : _pokemons) {
            delete p;
        }
    }

    void cadastrar_pokemon_eletrico(std::string nome, std::string tipo_ataque, double forca_ataque, double potencia_raio) {
        _pokemons.push_back(new PokemonEletrico(nome, tipo_ataque, forca_ataque, potencia_raio));
    }

    void cadastrar_pokemon_aquatico(std::string nome, std::string tipo_ataque, double forca_ataque, double litros_jato) {
        _pokemons.push_back(new PokemonAquatico(nome, tipo_ataque, forca_ataque, litros_jato));
    }

    void cadastrar_pokemon_explosivo(std::string nome, std::string tipo_ataque, double forca_ataque, double temperatura_explosao) {
        _pokemons.push_back(new PokemonExplosivo(nome, tipo_ataque, forca_ataque, temperatura_explosao));
    }

    Pokemon* usar_pokemon(int idpk) {
        return (idpk >= 0 && idpk < _pokemons.size()) ? _pokemons[idpk] : nullptr;
    }

    void imprimir_informacoes() const {
        std::cout << "Nome: " << _nome << std::endl;
        std::cout << "----------" << std::endl;
        if (_pokemons.empty()) {
            std::cout << "Nenhum Pokemon cadastrado!" << std::endl;
        } else {
            for (size_t i = 0; i < _pokemons.size(); ++i) {
                _pokemons[i]->imprimir_informacoes();
                std::cout << "----------" << std::endl;
            }
        }
    }

    std::string getNome() const { return _nome; }
};

// Definição da classe Campeonato
class Campeonato {
private:
    std::vector<Treinador*> _treinadores;

public:
    ~Campeonato() {
        for (Treinador* t : _treinadores) {
            delete t;
        }
    }

    void cadastrar_treinador(std::string nome) {
        _treinadores.push_back(new Treinador(nome));
    }

    void cadastrar_pokemon_eletrico(int idt, std::string nome, std::string tipo_ataque, double forca_ataque, double potencia_raio) {
        if (idt >= 0 && idt < _treinadores.size()) {
            _treinadores[idt]->cadastrar_pokemon_eletrico(nome, tipo_ataque, forca_ataque, potencia_raio);
        }
    }

    void cadastrar_pokemon_aquatico(int idt, std::string nome, std::string tipo_ataque, double forca_ataque, double litros_jato) {
        if (idt >= 0 && idt < _treinadores.size()) {
            _treinadores[idt]->cadastrar_pokemon_aquatico(nome, tipo_ataque, forca_ataque, litros_jato);
        }
    }

    void cadastrar_pokemon_explosivo(int idt, std::string nome, std::string tipo_ataque, double forca_ataque, double temperatura_explosao) {
        if (idt >= 0 && idt < _treinadores.size()) {
            _treinadores[idt]->cadastrar_pokemon_explosivo(nome, tipo_ataque, forca_ataque, temperatura_explosao);
        }
    }

    void imprimir_informacoes_treinador(int idt) const {
        if (idt >= 0 && idt < _treinadores.size()) {
            _treinadores[idt]->imprimir_informacoes();
        }
    }

    void executar_batalha(int idt1, int idpk1, int idt2, int idpk2) {
        if (idt1 >= 0 && idt1 < _treinadores.size() && idt2 >= 0 && idt2 < _treinadores.size()) {
            Pokemon* p1 = _treinadores[idt1]->usar_pokemon(idpk1);
            Pokemon* p2 = _treinadores[idt2]->usar_pokemon(idpk2);
            if (p1 && p2) {
                std::cout << "### Batalha ###" << std::endl;
                std::cout << _treinadores[idt1]->getNome() << " (" << p1->getNome() << ") vs. " << _treinadores[idt2]->getNome() << " (" << p2->getNome() << ")" << std::endl;
                p1->atacar(p2);
                p2->imprimir_status();
                std::cout << "#########" << std::endl;
            }
        }
    }
};

int main() {
    Campeonato campeonato;
    std::string comando;

    while (std::getline(std::cin, comando)) {
        std::istringstream iss(comando);
        std::string cmd;
        iss >> cmd;

        if (cmd == "t") {
            std::string nome;
            iss >> nome;
            campeonato.cadastrar_treinador(nome);
        } else if (cmd == "i") {
            int idt;
            iss >> idt;
            campeonato.imprimir_informacoes_treinador(idt);
        } else if (cmd == "e") {
            int idt;
            std::string nome, tipo_ataque;
            double forca_ataque, potencia_raio;
            iss >> idt >> nome >> tipo_ataque >> forca_ataque >> potencia_raio;
            campeonato.cadastrar_pokemon_eletrico(idt, nome, tipo_ataque, forca_ataque, potencia_raio);
        } else if (cmd == "q") {
            int idt;
            std::string nome, tipo_ataque;
            double forca_ataque, litros_jato;
            iss >> idt >> nome >> tipo_ataque >> forca_ataque >> litros_jato;
            campeonato.cadastrar_pokemon_aquatico(idt, nome, tipo_ataque, forca_ataque, litros_jato);
        } else if (cmd == "x") {
            int idt;
            std::string nome, tipo_ataque;
            double forca_ataque, temperatura_explosao;
            iss >> idt >> nome >> tipo_ataque >> forca_ataque >> temperatura_explosao;
            campeonato.cadastrar_pokemon_explosivo(idt, nome, tipo_ataque, forca_ataque, temperatura_explosao);
        } else if (cmd == "h") {
            int idt1, idpk1, idt2, idpk2;
            iss >> idt1 >> idpk1 >> idt2 >> idpk2;
            campeonato.executar_batalha(idt1, idpk1, idt2, idpk2);
        }
    }

    return 0;
}
