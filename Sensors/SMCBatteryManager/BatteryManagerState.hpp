//
//  BatteryManagerState.h
//  VirtualSMC
//
//  Copyright © 2018 usersse2. All rights reserved.
//

#ifndef BatteryManagerState_hpp
#define BatteryManagerState_hpp

/**
 *  Aggregated battery information
 */
struct BatteryInfo {
	/**
	 *  Unknown value (according to ACPI, -1)
	 */
	static constexpr uint32_t ValueUnknown = 0xFFFFFFFF;

	/**
	 *  Maximum integer value (according to ACPI)
	 */
	static constexpr uint32_t ValueMax = 0x80000000;

	/**
	 *  Must be no more than kSMBusMaximumDataSize
	 */
	static const size_t MaxStringLen = 32;

	/**
	 *  Default voltage to assume
	 */
	static constexpr uint32_t DummyVoltage = 12000;

	/**
	 *  Smaller state substruct for quick updates
	 */
	struct State {
		uint32_t state {0};
		uint32_t presentVoltage {0};
		uint32_t presentRate {0};
		uint32_t averageRate {0};
		uint32_t remainingCapacity {0};
		uint32_t lastFullChargeCapacity {0};
		uint32_t lastRemainingCapacity {0};
		uint32_t designVoltage {0};
		uint32_t runTimeToEmpty {0};
		uint32_t averageTimeToEmpty {0};
		int32_t signedPresentRate {0};
		int32_t signedAverageRate {0};
		uint32_t timeToFull {0};
		uint32_t designCapacityWarning {0};
		uint32_t designCapacityLow {0};
		bool powerUnitIsWatt {false};
		bool calculatedACAdapterConnected {false};
		bool bad {false};
	};

	/**
	 *  Complete battery information
	 */
	State state {};
	uint32_t designCapacity {0};
	uint32_t technology {0};
	uint32_t cycle {0};
	char deviceName[MaxStringLen] {};
	char serial[MaxStringLen] {};
	char batteryType[MaxStringLen] {};
	char manufacturer[MaxStringLen] {};
	bool connected {false};

	/**
	 *  Validate battery information and set the defaults
	 */
	void validateData();
};

/**
 *  Aggregated adapter information
 */
struct ACAdapterInfo {
	bool connected {false};
};

/**
 *  Aggregated battery manager state
 */
struct BatteryManagerState {
	/**
	 *  A total maximum of battery devices according to ACPI spec
	 */
	static constexpr uint8_t MaxBatteriesSupported = 4;

	/**
	 *  A total maximum of AC adapters according to ACPI spec
	 */
	static constexpr uint8_t MaxAcAdaptersSupported = 2;

	/**
	 * Set of battery infos
	 */
	BatteryInfo btInfo[MaxBatteriesSupported] {};

	/**
	 * Set of AC infos
	 */
	ACAdapterInfo acInfo[MaxAcAdaptersSupported] {};
};

#endif /* BatteryManagerState_hpp */
