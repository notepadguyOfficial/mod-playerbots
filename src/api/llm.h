#ifndef _OPENAI_HELPER_H
#define _OPENAI_HELPER_H

#include <atomic>
#include <string>
#include <vector>

class LLMInterface {
    LLMInterface() = default;
    LLMInterface(LLMInterface const&) = delete;
    LLMInterface& operator=(LLMInterface const&) = delete;
    ~LLMInterface() = default;
public:
    static LLMInterface* instance();

    static std::string SanitizeForJson(const std::string& input);
    static std::string Generate(const std::string& prompt, int timeOutSeconds, int maxGenerations, std::vector<std::string>& debugLines);
    static std::vector<std::string> ParseResponse(const std::string& response, const std::string& startPattern, const std::string& endPattern, const std::string& deletePattern, const std::string& splitPattern, std::vector<std::string>& debugLines);
    static void LimitContext(std::string& context, int currentLength);

private:
    std::atomic<int> generationCount = 0;
};

#define sLLMInterface LLMInterface::Instance()

#endif
