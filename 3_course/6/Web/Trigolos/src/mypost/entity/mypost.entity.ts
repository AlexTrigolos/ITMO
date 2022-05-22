import { User } from '../../users/entity/user.entity';
import { ApiProperty } from '@nestjs/swagger';
import { Column, Entity, ManyToOne, PrimaryGeneratedColumn } from 'typeorm';

@Entity()
export class MyPost {
  @ApiProperty()
  @PrimaryGeneratedColumn()
  id: number;

  @ApiProperty()
  @Column()
  title: string;

  @ApiProperty({ required: false })
  @Column()
  content?: string;

  @ApiProperty({ required: false })
  @Column()
  published?: boolean;

  @ApiProperty({ required: false, type: () => User })
  @ManyToOne(() => User, (user) => user.posts)
  author?: User;

  @ApiProperty({ required: false })
  @Column()
  authorId?: number;
}
