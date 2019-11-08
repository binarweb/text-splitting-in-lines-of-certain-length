// setari
#define SERIAL_BAUDRATE 9600

void stringSplitThreeTimes(const char *text, char *q1, char *q2, char *q3, uint8_t text_length) {
	// Split the text by space
	const uint8_t size1 = 50; // max words
	const uint8_t size2 = text_length;
	uint16_t i = 0, index1 = 0, index2 = 0;
	uint16_t len = strlen(text);
	char split[size1][size2];

	// Fill the split with NULL chars
	uint16_t j = 0;
	for (; j < size1; j++) {
		memset(split[j], 0, size2);
	}

	// Fill the questions with NULL chars
	memset(q1, 0, text_length);
	memset(q2, 0, text_length);
	memset(q3, 0, text_length);

	for (; i < len; i++) {
		if (
			text[i] == 32 ||  // 32 = space
			index2 == (size2 - 1) // no overflow
		) {
			split[index1][index2] = 0;
			index1++;
			index2 = 0;
			continue;
		}

		split[index1][index2] = text[i];
		index2++;

		if (index1 == (size1 - 1)) { // no overflow
			break;
		}
	}

	uint16_t m = 0;
	for (; m < size1; m++) {
		Serial.print(m);
		Serial.print(":");
		Serial.println(split[m]);
	}
	Serial.println("*****************");

	// Concat the text back in char array
	uint8_t k = 0;
	uint8_t index = 0;
	uint8_t last_len = 0;
	for (; k < size1; k++) {
		if (split[k][0] == 0) break; // there is no more splitted text

		uint8_t length = strlen(split[k]) + 1;

		if ((last_len + length) < (text_length - 2)) {
			if (index == 0) {
				if (last_len != 0) {
					strcat(q1, " ");
				}
				strcat(q1, split[k]);
			} else if (index == 1) {
				if (last_len != 0) {
					strcat(q2, " ");
				}
				strcat(q2, split[k]);
			} else if (index == 2) {
				if (last_len != 0) {
					strcat(q3, " ");
				}
				strcat(q3, split[k]);
			}
			last_len += length;
		} else {
			last_len = 0;
			index++;
			k--;
		}

		if (index == 3) break; // no overflow
	}
}

void setup() {
	Serial.begin(SERIAL_BAUDRATE);
	Serial.println("Start test");

	const uint8_t row_size = 20;
	char question1[row_size];
	char question2[row_size];
	char question3[row_size];

	stringSplitThreeTimes("Esti sigur ca vrei sa stergi toti senzorii?", &question1[0], &question2[0], &question3[0], row_size);

	Serial.print("question1:");
	Serial.println(question1);
	Serial.print("question2:");
	Serial.println(question2);
	Serial.print("question3:");
	Serial.println(question3);
	Serial.println("*****************");

	stringSplitThreeTimes("Ce mai face Ana? Are indeajuns de multe mere?", &question1[0], &question2[0], &question3[0], row_size);

	Serial.print("question1:");
	Serial.println(question1);
	Serial.print("question2:");
	Serial.println(question2);
	Serial.print("question3:");
	Serial.println(question3);
	Serial.println("*****************");

	stringSplitThreeTimes("Ce mai face Ana? Are mere?", &question1[0], &question2[0], &question3[0], row_size);

	Serial.print("question1:");
	Serial.println(question1);
	Serial.print("question2:");
	Serial.println(question2);
	Serial.print("question3:");
	Serial.println(question3);
	Serial.println("*****************");
}

void loop() {
}
