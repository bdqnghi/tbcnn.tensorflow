package com.github.Higman.hanoi;

import com.github.Higman.DrawableHanoiAlgorithm;
import kotlin.Unit;
import kotlin.jvm.functions.Function0;
import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class HanoiTowerAlgorithm extends HanoiAlgorithmComp implements DrawableHanoiAlgorithm {
    private Optional<HanoiTowerParameter> hanoiTowerParameter = Optional.empty();

    public HanoiTowerAlgorithm(Hanoi hanoi) {
        super(hanoi);
    }

    @Override
    public void execHanoi() {
        System.out.println("== Start");
        System.out.println(hanoi);
        initialize();
        do {
            System.out.println("========");
            if ( !firstStepWithOutput() ) { break; }   // 第1移動
            if ( !hanoi.isFinished() ) { break; }      // 終了判定
            if ( !secondStepWithOutput() ) { break; }  // 第2移動
            System.out.println(hanoi);
        } while ( !hanoi.isFinished() );
        hanoiTowerParameter = Optional.empty();
        System.out.println("== End");
        System.out.println(hanoi);
    }

    private boolean firstStepWithOutput() {
        Optional<MoveInformation> param = firstStep();
        if ( !param.isPresent() ) { return false; }                              // 例外判定
        param.ifPresent(info -> System.out.println("  = Move1: " + info.movingSource + " ==> " + info.destination));
        return true;
    }

    /**
     * 最小の円盤移動の処理
     *
     * @return 処理の成功/失敗
     */
    protected Optional<MoveInformation> firstStep() {
        if ( !hanoiTowerParameter.isPresent() ) { return Optional.empty(); }           // 例外判定
        HanoiTowerParameter param = hanoiTowerParameter.get();
        int nextTowerIndex = (param.towerIDHavingSmallestDisk.id + 1) % Hanoi.TowerID.values().length;
        Hanoi.TowerID nextTowerID = Hanoi.TowerID.values()[nextTowerIndex];
        MoveInformation mi = new MoveInformation(param.towerIDHavingSmallestDisk, nextTowerID);
        hanoi.move(param.towerIDHavingSmallestDisk, nextTowerID);                 // 円盤の移動
        updateStatusHanoiTower();
        return Optional.of(mi);
    }

    private boolean secondStepWithOutput() {
        Optional<MoveInformation> param = secondStep();
        if ( !param.isPresent() ) { return false; }                              // 例外判定
        param.ifPresent(info -> System.out.println("  = Move1: " + info.movingSource + " ==> " + info.destination));
        return true;
    }

    /**
     * 第2円盤の移動処理
     *
     * @return 処理の成功/失敗
     */
    protected Optional<MoveInformation> secondStep() {
        if ( !hanoiTowerParameter.isPresent() ) { return Optional.empty(); }           // 例外判定
        HanoiTowerParameter param = hanoiTowerParameter.get();
        MoveInformation mi = new MoveInformation(param.towerIDOfSecondTower, param.towerIDOfOtherTower);
        hanoi.move(param.towerIDOfSecondTower, param.towerIDOfOtherTower);                 // 円盤の移動
        updateStatusHanoiTower();
        return Optional.of(mi);
    }

    @Override
    public void initialize() {
        hanoiTowerParameter = Optional.of(new HanoiTowerParameter());
        updateStatusHanoiTower();
    }

    private void updateStatusHanoiTower() {
        hanoiTowerParameter.ifPresent(param -> {
            param.towerIDHavingSmallestDisk = getTowerIDHavingSmallestDisk();
            param.towerIDOfSecondTower = getTowerIDHavingSmallestDisk(param.towerIDHavingSmallestDisk);
            param.towerIDOfOtherTower = getTowerIDOfOtherTower(param.towerIDHavingSmallestDisk, param.towerIDOfSecondTower);
        });
    }

    @NotNull
    @Override
    public List<Function0<Optional<MoveInformation>>> getSortOperations() {
        return new ArrayList<Function0<Optional<MoveInformation>>>(Arrays.asList(() -> firstStep(), () -> secondStep()));
    }

    @NotNull
    @Override
    public Hanoi getHanoi() {
        return hanoi;
    }

    private class HanoiTowerParameter {
        public Hanoi.TowerID towerIDHavingSmallestDisk;
        public Hanoi.TowerID towerIDOfSecondTower;
        public Hanoi.TowerID towerIDOfOtherTower;

        public HanoiTowerParameter() {
        }

        public HanoiTowerParameter(Hanoi.TowerID towerIDHavingSmallestDisk, Hanoi.TowerID towerIDOfSecondTower, Hanoi.TowerID towerIDOfOtherTower) {
            this.towerIDHavingSmallestDisk = towerIDHavingSmallestDisk;
            this.towerIDOfSecondTower = towerIDOfSecondTower;
            this.towerIDOfOtherTower = towerIDOfOtherTower;
        }
    }
}
