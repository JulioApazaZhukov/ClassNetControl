/*#include "MainWindow.xaml.h"
#include <vector>
#include <string>
#include <msclr/marshal_cppstd.h>
#include <Windows.h>
#include <iostream>
#include <fstream>

using namespace System;
using namespace System::Windows;
using namespace System::Windows::Controls;

std::vector<std::string> allowedSites;

void ClassNetControl::MainWindow::OnAddSiteClick(System::Object^ sender, System::Windows::RoutedEventArgs^ e) {
    // Agregar sitio permitido
    std::string newSite = msclr::interop::marshal_as<std::string>(newSiteTextBox->Text);
    if (!newSite.empty() && std::find(allowedSites.begin(), allowedSites.end(), newSite) == allowedSites.end()) {
        allowedSites.push_back(newSite);
        allowedSitesList->Items->Add(gcnew String(newSite.c_str()));
        newSiteTextBox->Clear();
    }
}

void ClassNetControl::MainWindow::OnRemoveSiteClick(System::Object^ sender, System::Windows::RoutedEventArgs^ e) {
    // Eliminar sitio seleccionado
    if (allowedSitesList->SelectedItem != nullptr) {
        std::string selectedSite = msclr::interop::marshal_as<std::string>(allowedSitesList->SelectedItem->ToString());
        allowedSites.erase(std::remove(allowedSites.begin(), allowedSites.end(), selectedSite), allowedSites.end());
        allowedSitesList->Items->Remove(allowedSitesList->SelectedItem);
    }
}

void ClassNetControl::MainWindow::OnStartFilteringClick(System::Object^ sender, System::Windows::RoutedEventArgs^ e) {
    // Iniciar el filtrado de red (se puede conectar con WinDivert o reglas de firewall)
    std::ofstream outFile("allowed_sites.txt");
    for (const auto& site : allowedSites) {
        outFile << site << std::endl;
    }
    outFile.close();
    
    MessageBox::Show("Filtrado de red iniciado.");
    
    // Llamar a la lógica de WinDivert o Firewall para iniciar el bloqueo
    // system("start NetworkFilter.exe"); // Ejecutar la aplicación de filtrado
}*/