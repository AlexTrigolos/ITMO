import { MyPost } from '../../mypost/entity/mypost.entity';
import { ApiProperty } from '@nestjs/swagger';
import { Column, Entity, OneToMany, PrimaryGeneratedColumn } from 'typeorm';

@Entity()
export class User {
  @ApiProperty()
  @PrimaryGeneratedColumn()
  id: number;

  @ApiProperty({ uniqueItems: true })
  @Column()
  email: string;

  @ApiProperty({ required: false })
  @Column()
  name?: string;

  @ApiProperty({ isArray: true })
  @OneToMany(() => MyPost, (myPost) => myPost.author)
  posts: MyPost[];
}
