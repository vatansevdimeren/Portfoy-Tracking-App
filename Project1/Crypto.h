#ifndef  CRYPTO_H
#define CRYPTO_H
#include "Asset.h"
#include <string>
class Crypto : public Asset {
	private :
		std::string Network = "";
		bool IsStaked = false;
	public:
		Crypto(std::string AssetSymbol, double AssetAmount, double AssetAvaragePrice,
			std::string CryptoNetwork, bool StakedStatus);
		
		std::string GetNetwork();
		bool GetStakedStatus();

		void SetNetwork(std::string NewNetwork);
		void SetStakedStatus(bool NewStatus);

		void PrintAssetInfo() override;
};



#endif // ! CRYPTO_H
