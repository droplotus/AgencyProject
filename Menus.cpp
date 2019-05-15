#include "Menus.h"
using namespace std;

string choice;

void showAllTravelPacks(Agency agency) {
	agency.showTps(agency.getPackets());
	cout << "\t\t[1] Retroceder" << endl << endl;
	cout << "Opcao: ";
	string option = "-1";
	while (option != "1") {
		getline(cin, option);
		if (option != "1") cout << "Esta opcao nao existe, tente outra: ";
	}
}

void showTravelPacks(Agency & agency) {
	cout << endl << endl;
	cout << "\t _______________________________________________________________________" << endl;
	cout << "\t|\t\t\t\t\t\t\t\t\t|" << endl;
	cout << "\t|\t[1] Visualizar todos\t\t\t\t\t\t|" << endl;
	cout << "\t|\t[2] Visualizar todos com mesmo destino\t\t\t\t|" << endl;
	cout << "\t|\t[3] Visualizar todos entre duas datas\t\t\t\t|" << endl;
	cout << "\t|\t[4] Visualizar todos entre duas datas + mesmo destino\t\t|" << endl;
	cout << "\t|\t[5] Visualizar vendidos a um cliente\t\t\t\t|" << endl;
	cout << "\t|\t[6] Visualizar vendidos a todos os clientes\t\t\t|" << endl;
	cout << "\t|\t[7] Retroceder\t\t\t\t\t\t\t|" << endl;
	cout << "\t|\t\t\t\t\t\t\t\t\t|" << endl;
	cout << "\t|\t[0] SAIR\t\t\t\t\t\t\t|" << endl;
	cout << "\t|_______________________________________________________________________|" << endl << endl;
	cout << "Opção: ";

	bool accepted = false;
	getline(cin, choice);

	do {
		if (choice == "1") {
			accepted = true;
			showAllTravelPacks(agency);
			menuInformation(agency);
		}
		else if (choice == "2") {
			accepted = true;
			string place;
			cout << "Escolha um destino: ";
			getline(cin, place);
			agency.showTps(agency.showTravelPacksByPlace(agency.getPackets(), place));
			cout << "\t\t[1] Retroceder" << endl << endl;
			cout << "Opcao: ";
			string option = "-1";
			while (option != "1") {
				getline(cin, option);
				if (option != "1") cout << "Esta opcao nao existe, tente outra: ";
			}
			menuInformation(agency);
		}
		else if (choice == "3") {
			accepted = true;
			string date_1, date_2;
			cout << "Escolha uma data inicial: ";
			getline(cin, date_1);
			cout << "Escolha uma data final: ";
			getline(cin, date_2);
			agency.showTps(agency.showTravelPacksByDates(date_1, date_2));
			cout << "\t\t[1] Retroceder" << endl << endl;
			cout << "Opcao: ";
			string option = "-1";
			while (option != "1") {
				getline(cin, option);
				if (option != "1") cout << "Esta opcao nao existe, tente outra: ";
			}
			menuInformation(agency);
		}
		else if (choice == "4") {
			accepted = true;
			string date_1, date_2, place;
			cout << "Escolha uma data inicial: ";
			getline(cin, date_1);
			cout << "Escolha uma data final: ";
			getline(cin, date_2);
			cout << "Escolha um destino: ";
			getline(cin, place);
			agency.showTps(agency.showTravelPacksByDatesAndPlace(place, date_1, date_2));
			cout << "\t\t[1] Retroceder" << endl << endl;
			cout << "Opcao: ";
			string option = "-1";
			while (option != "1") {
				getline(cin, option);
				if (option != "1") cout << "Esta opcao nao existe, tente outra: ";
			}
			menuInformation(agency);
		}
		else if (choice == "5") {
			accepted = true;
			string nif;
			cout << "Escolha o NIF do cliente desejado: ";
			getline(cin, nif);
			agency.showTravelPacksFromClient(nif);
			menuInformation(agency);
		}
		else if (choice == "6") {
			accepted = true;
			agency.showTravelPacksFromAllClients();
			menuInformation(agency);
		}
		else if (choice == "7") {
			accepted = true;
			menuInformation(agency);
		}
		else if (choice == "0") {
			exit(0);
		}
		else {
			accepted = false;
			cout << "Esta opcao nao e possivel, escolha outra: ";
			getline(cin, choice);
		}
	} while (!accepted);
}

void menuClient(Agency & agency) {
	cout << "\t _______________________________________________" << endl;
	cout << "\t|\t\t\t\t\t\t|" << endl;
	cout << "\t|\t[1] Adicionar cliente\t\t\t|" << endl;
	cout << "\t|\t[2] Modificar cliente\t\t\t|" << endl;
	cout << "\t|\t[3] Remover cliente\t\t\t|" << endl;
	cout << "\t|\t[4] Retroceder\t\t\t\t|" << endl;
	cout << "\t|\t\t\t\t\t\t|" << endl;
	cout << "\t|\t[0] SAIR\t\t\t\t|" << endl;
	cout << "\t|_______________________________________________|" << endl << endl;
	cout << "Opcao: ";

	bool accepted = false;
	getline(cin, choice);

	do {
		if (choice == "1") {
			accepted = true;
			agency.createClient();
			menuClient(agency);
		}
		else if (choice == "2") {
			accepted = true;
			agency.justShowAllClients();
			cout << endl << "Escolha o NIF do cliente a alterar: ";
			string nif;
			getline(cin, nif);
			agency.editClient(nif);
			menuClient(agency);
		}
		else if (choice == "3") {
			accepted = true;
			cout << "Escolha o NIF do cliente a remover: ";
			string nif;
			getline(cin, nif);
			agency.removeClient(nif);
			menuClient(agency);
		}
		else if (choice == "4") {
			accepted = true;
			mainMenu(agency);
		}
		else if (choice == "0") {
			exit(0);
		}
		else {
			cout << "Esta opcao nao e possivel, escolha outra: ";
			getline(cin, choice);
		}
	} while (!accepted);
}

void menuPack(Agency & agency) {
	cout << "\t _______________________________________________" << endl;
	cout << "\t|\t\t\t\t\t\t|" << endl;
	cout << "\t|\t[1] Adicionar pack\t\t\t|" << endl;
	cout << "\t|\t[2] Modificar pack\t\t\t|" << endl;
	cout << "\t|\t[3] Remover pack\t\t\t|" << endl;
	cout << "\t|\t[4] Retroceder\t\t\t\t|" << endl;
	cout << "\t|\t\t\t\t\t\t|" << endl;
	cout << "\t|\t[0] SAIR\t\t\t\t|" << endl;
	cout << "\t|_______________________________________________|" << endl << endl;
	cout << "Opcao: ";

	bool accepted = false;
	getline(cin, choice);

	do {
		if (choice == "1") {
			accepted = true;
			agency.createTravelPack();
			menuPack(agency);
		}
		else if (choice == "2") {
			accepted = true;
			cout << "Escolha o ID do pack a alterar: ";
			string id;
			getline(cin, id);
			agency.editTravelPack(id);
			menuPack(agency);
		}
		else if (choice == "3") {
			accepted = true;
			cout << "Escolha o ID do pack a remover: ";
			string id;
			getline(cin, id);
			agency.removeTravelPack(id);
			menuPack(agency);
		}
		else if (choice == "4") {
			mainMenu(agency);
		}
		else if (choice == "0") {
			exit(0);
		}
		else {
			cout << "Esta opcao nao e possivel, escolha outra: ";
			getline(cin, choice);
		}
	} while (!accepted);
}

void menuInformation(Agency & agency) {
	cout << endl << endl;
	cout << "\t _______________________________________________" << endl;
	cout << "\t|\t\t\t\t\t\t|" << endl;
	cout << "\t|\t[1] Visualizar cliente\t\t\t|" << endl;
	cout << "\t|\t[2] Visualizar clientes\t\t\t|" << endl;
	cout << "\t|\t[3] Visualizar pacote turistico\t\t|" << endl;
	cout << "\t|\t[4] Visualizar pacotes turisticos\t|" << endl;
	cout << "\t|\t[5] Retroceder\t\t\t\t|" << endl;
	cout << "\t|\t\t\t\t\t\t|" << endl;
	cout << "\t|\t[0] SAIR\t\t\t\t|" << endl;
	cout << "\t|_______________________________________________|" << endl << endl;
	cout << "Opcao: ";

	bool accepted = false;
	getline(cin, choice);

	do {
		if (choice == "1") {
			accepted = true;
			cout << "Escolha o NIF do cliente: ";
			string nif;
			getline(cin, nif);
			agency.showClient(nif);
			menuInformation(agency);
		}
		else if (choice == "2") {
			accepted = true;
			agency.showAllClients();
			menuInformation(agency);
		}
		else if (choice == "3") {
			accepted = true;
			cout << "Escolha o ID do pack: ";
			string id;
			getline(cin, id);
			agency.showTravelPack(id);
			menuInformation(agency);
		}
		else if (choice == "4") {
			accepted = true;
			showTravelPacks(agency);
		}
		else if (choice == "5") {
			accepted = true;
			mainMenu(agency);
		}
		else if (choice == "0") {
			exit(0);
		}
		else {
			accepted = false;
			cout << "Esta opcao nao e possivel, escolha outra: ";
			getline(cin, choice);
		}
	} while (!accepted);
}

void menuHelp(Agency & agency) {
	cout << endl << endl;
	cout << "\t\t _________________________________________________________" << endl;
	cout << "\t\t|\t\t\t\t\t\t\t  |" << endl;
	cout << "\t\t|\t\t     ________              _________\t  |" << endl;
	cout << "\t\t|\t||\t||  ||\t       ||         ||       ||\t  |" << endl;
	cout << "\t\t|\t||______||  ||_______  ||         ||_______||\t  |" << endl;
	cout << "\t\t|\t||\t||  ||\t       ||         ||\t\t  |" << endl;
	cout << "\t\t|\t||\t||  ||_______  ||_______  ||\t\t  |" << endl;
	cout << "\t\t|\t\t\t\t\t\t\t  |" << endl;
	cout << "\t\t|_________________________________________________________|" << endl << endl;
	cout << "\t" << "_Este menu e uma ajuda para como usar este programa." << endl << endl;
	cout << "\t" << "_Quando o usar para guardar informacao, jamais use caracteres especiais pois pode dar um erro" << endl;
	cout << "\t" << "	em certas funcoes tanto a calcular informacao como a visualizar." << endl << endl;
	cout << "\t" << "_Se estiver a usar em linux, deixe o terminal maior ou igual que 150 de largura." << endl << endl;
	cout << "\t" << "_Se estiver a usar em windows, deixe o terminal em fullscreen pois nao testei." << endl << endl;
	cout << "\t" << "_Sempre que guardar informacao, use as seguintes formas de fazer:" << endl;
	cout << "\t" << "	Escrever uma morada: rua / nr. porta / andar (pode ser - se nao houver) / codigo-postal / localidade" << endl;
	cout << "\t" << "	Escrever uma data  : dia / mes / ano" << endl << endl;
	cout << "\t" << "_Para modificar tanto um cliente como um pacote turistico, o programa mostra o que" << endl;
	cout << "\t" << "	ja esta guardado em memoria, se deseja apenas mudar um ID ou uma RUA, tera de" << endl;
	cout << "\t" << "	recopiar tudo e mudar so o desejado." << endl << endl;
	cout << "\t" << "__IMPORTANTE__" << endl;
	cout << "\t" << "	O programa assume que voce escreveu tudo bem, entao trate de o fazer." << endl;
	cout << "\t" << "	Exemplo: se voce escrever letras envez de numeros numa data, vai aceitar" << endl;
	cout << "\t" << "	so tera alguns erros e depois tera de modificar o ficheiro de texto eventualmente." << endl << endl;
	cout << "\t" << "[1] RETROCEDER" << endl;
	cout << "\t" << "[0] SAIR" << endl << endl;
	cout << "Opcao: ";

	bool accepted = false;
	getline(cin, choice);

	do {
		if (choice == "1") {
			accepted = true;
			mainMenu(agency);
		}
		else if (choice == "0") {
			exit(0);
		}
		else {
			accepted = false;
			cout << "Esta opcao nao e possivel, escolha outra: ";
			getline(cin, choice);
		}
	} while (!accepted);
}

unsigned mainMenu(Agency & agency) {

	cout << endl << endl;
	cout << "\tAgencia:\t" << agency.getName() << endl;
	cout << "\tNIF:\t\t" << agency.getVATnumber() << endl;
	cout << "\tURL:\t\t" << agency.getURL() << endl;
	cout << "\tEndereco:\t" << agency.getAddress().getStreet() << " / " << agency.getAddress().getDoorNumber() << " / " << agency.getAddress().getFloor() << " / " << agency.getAddress().getPostalCode() << " / " << agency.getAddress().getLocation() << endl << endl;
	//cout << "\tPacotes vendidos: \t" << totalTravelPacksBought() << endl << "\tValor total: \t\t" << totalIncome() << " €" << endl;
	cout << "\t _______________________________________________" << endl;
	cout << "\t|\t\t\t\t\t\t|" << endl;
	cout << "\t|\t[1] Gestão de clientes\t\t\t|" << endl;
	cout << "\t|\t[2] Gestão de pacotes turisticos\t|" << endl;
	cout << "\t|\t[3] Visualizacao de informação\t|" << endl;
	cout << "\t|\t[4] Compra de pacotes turisticos\t|" << endl;
	cout << "\t|\t\t\t\t\t\t|" << endl;
	cout << "\t|\t[5] AJUDA\t\t\t\t|" << endl;
	cout << "\t|\t[0] SAIR\t\t\t\t|" << endl;
	cout << "\t|_______________________________________________|" << endl << endl;
	cout << "Opcao: ";

	bool accepted = false;
	getline(cin, choice);

	do {
		if (choice == "1") {
			accepted = true;
			menuClient(agency);
		}
		else if (choice == "2") {
			accepted = true;
			menuPack(agency);
		}
		else if (choice == "3") {
			accepted = true;
			menuInformation(agency);
		}
		else if (choice == "4") {
			accepted = true;
			string nif;
			cout << "Escolha o NIF do cliente que efetua a compra: ";
			getline(cin, nif);
			agency.buyTravelPack(nif);
			mainMenu(agency);
		}
		else if (choice == "5") {
			accepted = true;
			menuHelp(agency);
		}
		else if (choice == "0") {
			exit(0);
		}
		else {
			cout << "Esta opcao nao e possivel, escolha outra: ";
			getline(cin, choice);
		}
	} while (!accepted);

	return 0;
}

