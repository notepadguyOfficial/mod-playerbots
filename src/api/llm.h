#ifndef _OPENAI_HELPER_H
#define _OPENAI_HELPER_H

#include <atomic>
#include <string>
#include <vector>

class LLMInterface {
public:
    LLMInterface() {}
    LLMInterface(const LLMInterface&) = delete;
    LLMInterface& operator=(const LLMInterface&) = delete;

    static LLMInterface& Instance()
    {
        static LLMInterface instance;
        return instance;
    }

    static std::string SanitizeForJson(const std::string& input);
    static std::string Generate(const std::string& prompt, int timeOutSeconds, int maxGenerations, std::vector<std::string>& debugLines);
    static std::vector<std::string> ParseResponse(const std::string& response, const std::string& startPattern, const std::string& endPattern, const std::string& deletePattern, const std::string& splitPattern, std::vector<std::string>& debugLines);
    static void LimitContext(std::string& context, int currentLength);

private:
    std::atomic<int> generationCount = 0;
};

#define sLLMInterface LLMInterface::Instance()

#endif
