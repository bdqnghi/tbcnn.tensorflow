#include <experimental/string_view>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

namespace std { using std::experimental::string_view; }
enum Attribute{
    NONE, LOW, HIGH,
    DISCRETE, CONTINIOUS,
    ATTRIBUTE_SIZE
};

struct ClassificationData{
    ClassificationData() = default;
    ClassificationData(const ClassificationData&) = default;
    ClassificationData& operator=(ClassificationData&& toMove) noexcept{
        this->attributes = std::move(toMove.attributes);
        return *this;
    }
    std::unordered_map<std::string, Attribute> attributes;
};

struct Classification{
    void addData(Attribute domain, Attribute setSize, Attribute noise){
        this->m_ClassificationsData.emplace_back();
        auto& attributes = this->m_ClassificationsData.back().attributes;
        attributes["Domain"] = domain;
        attributes["Trainingssetsize"] = setSize;
        attributes["Noise"] = noise;
    }
    void calculateProbabilities(){
        // search for domain
        size_t counter0 = 0, counter1 = 0, counter2 = 0;
        for (auto& e : this->m_ClassificationsData){
            if (e.attributes["Domain"] == Attribute::DISCRETE)
                ++counter0;
            else
                ++counter1;
        }
        this->m_DomainProbabilities[Attribute::DISCRETE] = float(counter0) / float(counter0 + counter1);
        this->m_DomainProbabilities[Attribute::CONTINIOUS] = float(counter1) / float(counter0 + counter1);


        // training set size
        counter0 = 0; counter1 = 0; counter2 = 0;
        for (auto& e : this->m_ClassificationsData){
            if (e.attributes["Trainingssetsize"] == Attribute::LOW)
                ++counter0;
            else
                ++counter1;
        }
        this->m_SetSizeProbabilities[Attribute::LOW] = float(counter0) / float(counter0 + counter1);
        this->m_SetSizeProbabilities[Attribute::HIGH] = float(counter1) / float(counter0 + counter1);


        // noise
        counter0 = 0; counter1 = 0; counter2 = 0;
        for (auto& e : this->m_ClassificationsData){
            if (e.attributes["Noise"] == Attribute::NONE)
                ++counter0;
            else if (e.attributes["Noise"] == Attribute::LOW)
                ++counter1;
            else
                ++counter2;
        }
        this->m_NoiseProbablilities[Attribute::NONE] = float(counter0) / float(counter0 + counter1 + counter2);
        this->m_NoiseProbablilities[Attribute::LOW] = float(counter1) / float(counter0 + counter1 + counter2);
        this->m_NoiseProbablilities[Attribute::HIGH] = float(counter2) / float(counter0 + counter1 + counter2);
    }

    float getNaiveBayesPart(Attribute domain, Attribute setSize, Attribute noise){
        return this->m_DomainProbabilities[domain] * this->m_SetSizeProbabilities[setSize] * this->m_NoiseProbablilities[noise];
    }

private:
    std::vector<ClassificationData> m_ClassificationsData;
    std::array<float, Attribute::ATTRIBUTE_SIZE> m_DomainProbabilities;
    std::array<float, Attribute::ATTRIBUTE_SIZE> m_NoiseProbablilities;
    std::array<float, Attribute::ATTRIBUTE_SIZE> m_SetSizeProbabilities;
};


struct NaiveBayes{
    void readTrainingsData(std::string_view str){
        size_t domain_d = 0, domain_c = 0;
        size_t netSize_l = 0, netSize_h = 0;
        size_t noise_n = 0, noise_l = 0, noise_h = 0;

        std::fstream file(str.to_string(), std::fstream::in);
        std::string line;
        std::getline(file, line);
        while(std::getline(file, line)){
            std::string domain, setSize, noise, name;
            std::stringstream sstr(line);
            std::getline(sstr, domain , ',');
            std::getline(sstr, setSize, ' '); std::getline(sstr, setSize, ',');
            std::getline(sstr, noise  , ' '); std::getline(sstr, noise  , ',');
            std::getline(sstr, name   , ' '); std::getline(sstr, name);
            const Attribute d = domain == "discrete" ? Attribute::DISCRETE : Attribute::CONTINIOUS;
            const Attribute s = setSize == "low" ? Attribute::LOW : Attribute::HIGH;
            const Attribute n = noise == "none" ? Attribute::NONE : noise == "low" ? Attribute::LOW : Attribute::HIGH;
            this->m_Classifications[name].addData(d, s, n);
            this->m_ClassificationProbability[name] += 1.f;
        }
        for (auto& e : this->m_Classifications)
            e.second.calculateProbabilities();

        for (auto& e : this->m_ClassificationProbability)
            e.second /= float(this->m_ClassificationProbability.size());

        this->m_DomainProbabilities[Attribute::DISCRETE] = float(domain_d) / float(domain_c + domain_c);
        this->m_DomainProbabilities[Attribute::CONTINIOUS] = float(domain_c) / float(domain_c + domain_c);

        this->m_SetSizeProbabilities[Attribute::LOW] = float(netSize_l) / float(netSize_l + netSize_h);
        this->m_SetSizeProbabilities[Attribute::HIGH] = float(netSize_h) / float(netSize_l + netSize_h);

        this->m_NoiseProbablilities[Attribute::NONE] = float(noise_n) / float(noise_n + noise_l + noise_h);
        this->m_NoiseProbablilities[Attribute::LOW] = float(noise_l) / float(noise_n + noise_l + noise_h);
        this->m_NoiseProbablilities[Attribute::HIGH] = float(noise_h) / float(noise_n + noise_l + noise_h);
    }
    std::pair<std::string, float> findBestClassification(Attribute domain, Attribute setSize, Attribute noise) {
        std::string bestClassification;
        float bestProbability = 0.f;
        auto calcProb = [this, &domain, &setSize, &noise](auto& e){
            float prob = e.second.getNaiveBayesPart(domain, setSize, noise);
            prob *= this->m_ClassificationProbability[e.first];
            prob /= (this->m_DomainProbabilities[domain] * this->m_SetSizeProbabilities[setSize] * this->m_NoiseProbablilities[noise]);
            return prob;
        };

        for (auto& e : this->m_Classifications){
            const float prob = calcProb(e);
            if (bestProbability < prob){
                bestProbability = prob;
                bestClassification = e.first;
            }
        }
        return {bestClassification, bestProbability};
    }
private:
    std::unordered_map<std::string, Classification> m_Classifications;
    std::unordered_map<std::string, float> m_ClassificationProbability;

    std::array<float, Attribute::ATTRIBUTE_SIZE> m_DomainProbabilities;
    std::array<float, Attribute::ATTRIBUTE_SIZE> m_NoiseProbablilities;
    std::array<float, Attribute::ATTRIBUTE_SIZE> m_SetSizeProbabilities;
};

constexpr size_t hash_function(const char* str){
    size_t res = 0;
    for (size_t i = 0; str[i]; ++i)
        res += size_t(str[i]);
    return res;
}

[[noreturn]]
int main(){
    NaiveBayes bayes;
    std::cout << "start training" << std::endl;
    bayes.readTrainingsData(FILE_PATH "trainingset.csv");

    auto convertString2Attribute = [](const std::string& str){
        switch (hash_function(str.c_str())){
        case hash_function("none"): return Attribute::NONE;
        case hash_function("low"):  return Attribute::LOW;
        case hash_function("high"): return Attribute::HIGH;
        case hash_function("discrete"):   return Attribute::DISCRETE;
        case hash_function("continious"): return Attribute::CONTINIOUS;
        default: throw std::runtime_error("Cannot parse: " + str);
        }
    };

    std::cout << "training complete, please enter query:\n" << std::endl;
    while (true){
        Attribute domain, setSize, noise;
        std::string str;

        std::cout << "Domain: " << std::flush;
        std::getline(std::cin, str);
        domain = convertString2Attribute(str);

        std::cout << "Trainings set size: " << std::flush;
        std::getline(std::cin, str);
        setSize = convertString2Attribute(str);

        std::cout << "Noise: " << std::flush;
        std::getline(std::cin, str);
        noise = convertString2Attribute(str);

        auto result = bayes.findBestClassification(domain, setSize, noise);
        std::cout << result.first << ", prob: " << result.second << std::endl;
    }
}

