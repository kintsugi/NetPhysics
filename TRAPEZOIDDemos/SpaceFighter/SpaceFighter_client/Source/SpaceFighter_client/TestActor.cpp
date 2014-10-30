#include "SpaceFighter_client.h"
#include "TestActor.h"

ATestActor::ATestActor(const FPostConstructInitializeProperties &PCIP) : Super(PCIP) {}

void ATestActor::networkUpdate() {
	test = 1;
}