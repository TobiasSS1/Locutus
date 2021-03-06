#pragma once

#include "Common.h"

namespace UAlbertaBot
{
class LocutusUnit
{
    BWAPI::Unit     unit;

    // Used for pathing
    BWAPI::Position                     targetPosition;
    std::deque<const BWEM::ChokePoint*> waypoints;
    BWAPI::Unit                         mineralWalkingPatch;
    int                                 lastMoveFrame;

    // Used for various things, like detecting stuck goons and updating our collision matrix
    BWAPI::Position lastPosition;

    // Used for goon micro
    int lastAttackStartedAt;
    int potentiallyStuckSince;  // frame the unit might have been stuck since, or 0 if it isn't stuck

    void updateMoveWaypoints();
    void moveToNextWaypoint();
    void mineralWalk();
    std::vector<const BWEM::ChokePoint *> pathAvoidingUnusableChokes(
        BWAPI::Position start,
        BWAPI::Position target,
        int minChokeWidth,
        int desiredChokeWidth = 0);

    void updateGoon();

public:
    LocutusUnit()
        : unit(nullptr)
        , targetPosition(BWAPI::Positions::Invalid)
        , mineralWalkingPatch(nullptr)
        , lastMoveFrame(0)
        , lastAttackStartedAt(0)
        , lastPosition(BWAPI::Positions::Invalid)
        , potentiallyStuckSince(0)
    {
    }

    LocutusUnit(BWAPI::Unit unit)
        : unit(unit)
        , targetPosition(BWAPI::Positions::Invalid)
        , mineralWalkingPatch(nullptr)
        , lastMoveFrame(0)
        , lastAttackStartedAt(0)
        , lastPosition(BWAPI::Positions::Invalid)
        , potentiallyStuckSince(0)
    {
    }

    void update();

    bool moveTo(BWAPI::Position position, bool avoidNarrowChokes = false);
    void fleeFrom(BWAPI::Position position);
    int  distanceToMoveTarget() const;

    bool isReady() const;
    bool isStuck() const;

    int getLastAttackStartedAt() const { return lastAttackStartedAt; };
};
}