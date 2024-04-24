#include <iostream>
#include <windows.h>
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi.lib")

// Função para modificar o registro do Windows
bool modificarRegistro(const char* chave, const char* valor) {
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, chave, 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) {
        std::cout << "Erro ao abrir a chave do registro: " << chave << std::endl;
        return false;
    }

    if (RegSetValueEx(hKey, "MachineGuid", 0, REG_SZ, (BYTE*)valor, strlen(valor) + 1) != ERROR_SUCCESS) {
        std::cout << "Erro ao definir o novo valor para a chave do registro: " << chave << std::endl;
        RegCloseKey(hKey);
        return false;
    }

    RegCloseKey(hKey);
    return true;
}

// Função para mascarar o endereço IP
bool falsificarEnderecoIP(const char* novoIP) {
    // Essa é apenas uma simulação, não estamos realmente alterando o endereço IP do computador
    std::cout << "Endereço IP falsificado para: " << novoIP << std::endl;
    return true;
}

// Função para mascarar informações sensíveis
void mascararInformacoes() {
    // Mascarar HWID
    const char novoHWID[] = "f47ac10b-58cc-4372-a567-0e02b2c3d479";
    if (!modificarRegistro("SOFTWARE\\Microsoft\\Cryptography", novoHWID))
        return;

    // Mascarar ProductID
    const char novoProductID[] = "12345-ABCDE-FGHIJ-KLMNO-PQRST";
    if (!modificarRegistro("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", novoProductID))
        return;

    // Mascarar InstallDate
    const char novoInstallDate[] = "20240101";
    if (!modificarRegistro("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", novoInstallDate))
        return;

    // Mascarar ComputerName
    const char novoComputerName[] = "NomeDoComputadorMascarado";
    if (!SetComputerNameA(novoComputerName))
        std::cout << "Erro ao definir o novo nome do computador." << std::endl;

    // Falsificar o endereço IP
    const char novoIP[] = "192.168.1.100"; // Novo endereço IP fictício
    if (!falsificarEnderecoIP(novoIP))
        std::cout << "Erro ao falsificar o endereço IP." << std::endl;
}

int main() {
    // Verificar se o programa está sendo executado com privilégios de administrador
    if (IsUserAnAdmin()) {
        mascararInformacoes();
        std::cout << "Informacoes mascaradas com sucesso!" << std::endl;
    } else {
        std::cout << "Erro: O programa deve ser executado com privilégios de administrador." << std::endl;
    }
    return 0;
}

